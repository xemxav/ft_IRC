//
// Created by Xavier-Emmanuel Moreau on 27/04/2020.
//

#include "../../includes/ft_irc.h"


int recv_line(int sock, unsigned char *dest_buffer)
{
	unsigned char	*ptr;
	int				eol_matched;

	ptr = dest_buffer;
	eol_matched = 0;
	while (recv(sock, dest_buffer, 1, 0) == 1)
	{
		if (*ptr == EOL[eol_matched])
		{
			eol_matched++;
			if (eol_matched == EOL_SIZE)
			{
				*(ptr + 1 + EOL_SIZE) = '\0';
				return (strlen((char*)dest_buffer));
			}
			else
				eol_matched = 0;
		}
		else
			ptr++;

	}
	return (0);
}