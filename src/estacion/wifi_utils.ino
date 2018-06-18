void wifi_init_client (Stream *stream) {
	at_command (stream, "AT+CWAUTOCONN=0"); // Deshabilitar conexion automática
	bool success = at_command (stream, "AT+CWMODE=1"); // Modo cliente
	return success;
}

bool wifi_connect_ssid (Stream *stream, char *ssid, char *password) {
	char *format = "AT+CWJAP=\"%s\",\"%s\"";
	int len  = strlen (format) + strlen (ssid) + strlen (password) +1;
	char *command = malloc (len);
	sprintf (command, format, ssid, password);
	bool success = at_command (stream, command);
	free (command);
	return success;

}
