#define HTTP_SERIAL_DEBUG 1

bool http_post (Stream *stream, char *host, int port, char *resource, char *post_data) {
	bool success = false;
	char *start_command ="AT+CIPSTART=\"TCP\",\"%s\",%d";
	int len = strlen(start_command) + strlen (host) + strlen (resource) + 11;
	char *command = malloc (len);
	sprintf (command, start_command, host, port);
	success = at_command (stream, command);
	free (command);

	if (!success) {
		return false;
	}

	char *request_format =
		"POST %s HTTP/1.1\r\n"
		"Host: %s\r\n"
		"Content-Length: %d\r\n"
		"Content-Type: application/x-www-form-urlencoded\r\n"
		"\r\n"
		"%s";

	char *request = malloc (strlen (request_format) + strlen (resource) + strlen (host) + strlen (post_data) + 11);
	sprintf (request, request_format, resource, host, strlen (post_data), post_data);


	char *send_command = "AT+CIPSENDBUF=%d";
	command = malloc (strlen (send_command) +11);
	sprintf (command, send_command, strlen (request));
	success = at_command (stream, command);
	free (command);

	if (!success) {
		return false;
	}

	if (HTTP_SERIAL_DEBUG) {
		Serial.println ("++ HTTP REQUEST");
		Serial.println (request);
		Serial.println ("++");
	}

	stream-> print (request);
	free (request);

	delay (1200); // La documentación dice que debe esperarsse al menos un segundo antes de enviar el comando CIPCLOSE
	success = at_command (stream, "AT+CIPCLOSE");
	return success;
}
