#define AT_SERIAL_DEBUG 1

bool at_command (Stream *stream, char *command) {
	at_flush (stream);
	if (AT_SERIAL_DEBUG) {
		Serial.print (">>> ");
		Serial.println (command);
	}
	bool success = false;
	char *send_str = malloc (strlen (command) +3);
	strcpy (send_str, command);
	strcat (send_str, "\r\n");
	bool must_send = true;
	while (must_send) {
		stream-> print (send_str);
		bool must_read_line = true;
		char *line = NULL;
		while (must_read_line) {
			line = at_read_line (stream);
			if (AT_SERIAL_DEBUG) {
				Serial.print ("<<< ");
				Serial.println (line);
			}
			if (at_response_ok (line)) {
				must_read_line = false;
				must_send = false;
				success = true;
			} else if (at_response_error (line) || at_response_fail (line)) {
				must_read_line = false;
				must_send = false;
				success = false;
			} else if (at_response_busy (line)) {
				must_read_line = false;
				must_send = true;
				delay (300);
			}
			free (line);
		}
	}
	free (send_str);
	return success;
}

char *at_read_line (Stream *stream) {
	String readed = stream-> readStringUntil('\n');
	int buf_len = readed.length () +1;
	char *response = malloc (buf_len);
	readed.toCharArray (response, buf_len);
	return response;
}

bool at_response_busy (char *response) {
	return (strncmp (response, "busy", 4) == 0);
}

bool at_response_ok (char *response) {
	return (strncmp (response, "OK\r", 3) == 0) || (strncmp (response, "SEND OK\r", 8) == 0);
}

bool at_response_error (char *response) {
	return (strncmp (response, "ERROR\r", 6) == 0);
}

bool at_response_fail (char *response) {
	return (strncmp (response, "FAIL\r", 5) == 0) || (strncmp (response, "SEND FAIL\r", 10) == 0);
}

bool at_flush (Stream *stream) {
	if (AT_SERIAL_DEBUG) {
		Serial.print("** flushing ");
		while (stream-> available()) {
			Serial.write (stream-> read());
		}
		Serial.println(" **");
	} else {
		while (stream-> available()) {
			stream-> read();
		}
	}
}
