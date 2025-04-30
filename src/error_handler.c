/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:21:18 by slangero          #+#    #+#             */
/*   Updated: 2025/04/30 14:21:34 by slangero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_handler.h"

// Initialize default error context
t_error_context	create_error_context(void)
{
	t_error_context	ctx;

	ctx.line_number = -1;
	ctx.element = NULL;
	ctx.detail = NULL;
	return (ctx);
}

// Set line number in error context
void	set_error_line(t_error_context *ctx, int line)
{
	if (ctx)
		ctx->line_number = line;
}

// Set element in error context
void	set_error_element(t_error_context *ctx, char *element)
{
	if (ctx)
		ctx->element = element;
}

// Set detail in error context
void	set_error_detail(t_error_context *ctx, char *detail)
{
	if (ctx)
		ctx->detail = detail;
}

// Get error type from error code
t_error_type	get_error_type(t_error_code code)
{
	if (code >= 100 && code < 200)
		return (ERR_FILE);
	else if (code >= 200 && code < 300)
		return (ERR_PARSE);
	else if (code >= 300 && code < 400)
		return (ERR_VALIDATE);
	else
		return (ERR_MEMORY);
}

// Get error message from error code
const char	*get_error_message(t_error_code code)
{
	static const char	*messages[] = {
		[ERR_FILE_NOT_FOUND] = "File not found",
		[ERR_FILE_PERMISSION] = "Permission denied",
		[ERR_FILE_EXTENSION] = "Invalid file extension",
		[ERR_FILE_EMPTY] = "File is empty",
		
		[ERR_PARSE_INVALID_IDENTIFIER] = "Invalid identifier",
		[ERR_PARSE_MISSING_VALUE] = "Missing value for identifier",
		[ERR_PARSE_DUPLICATE_ELEMENT] = "Duplicate element definition",
		[ERR_PARSE_INVALID_COLOR] = "Invalid color format",
		[ERR_PARSE_INVALID_TEXTURE] = "Invalid texture path",
		
		[ERR_VALIDATE_MAP_OPEN] = "Map is not completely enclosed by walls",
		[ERR_VALIDATE_MAP_CHARS] = "Invalid character in map",
		[ERR_VALIDATE_PLAYER_MISSING] = "No player position found in map",
		[ERR_VALIDATE_PLAYER_MULTIPLE] = "Multiple player positions found",
		
		[ERR_MEMORY_ALLOC] = "Memory allocation failed"
	};
	
	if (code >= 100 && code < sizeof(messages) / sizeof(messages[0]) && 
		messages[code] != NULL)
		return (messages[code]);
	return ("Unknown error");
}

// Central error handling function
int	handle_error(t_error_code code, t_error_context *ctx)
{
	t_error_type	type;
	const char		*message;

	type = get_error_type(code);
	message = get_error_message(code);
	
	ft_putstr_fd("Error\n", 2);
	
	// Print error type prefix
	if (type == ERR_FILE)
		ft_putstr_fd("File error: ", 2);
	else if (type == ERR_PARSE)
		ft_putstr_fd("Parse error: ", 2);
	else if (type == ERR_VALIDATE)
		ft_putstr_fd("Validation error: ", 2);
	else if (type == ERR_MEMORY)
		ft_putstr_fd("Memory error: ", 2);
	
	// Print main error message
	ft_putstr_fd((char *)message, 2);
	
	// Print context information if available
	if (ctx)
	{
		if (ctx->line_number >= 0)
		{
			ft_putstr_fd(" at line ", 2);
			ft_putnbr_fd(ctx->line_number, 2);
		}
		
		if (ctx->element)
		{
			ft_putstr_fd(" (", 2);
			ft_putstr_fd(ctx->element, 2);
			ft_putstr_fd(")", 2);
		}
		
		if (ctx->detail)
		{
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(ctx->detail, 2);
		}
	}
	
	ft_putstr_fd("\n", 2);
	return (0);
}