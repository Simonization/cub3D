/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:21:48 by slangero          #+#    #+#             */
/*   Updated: 2025/04/30 14:21:56 by slangero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HANDLER_H
# define ERROR_HANDLER_H

# include "libft.h"

// Error categories
typedef enum e_error_type
{
	ERR_FILE,      // File-related errors (access, format)
	ERR_PARSE,     // Parsing errors (syntax, structure)
	ERR_VALIDATE,  // Validation errors (map integrity, player)
	ERR_MEMORY     // Memory allocation errors
}	t_error_type;

// Specific error codes
typedef enum e_error_code
{
	// File errors (100-199)
	ERR_FILE_NOT_FOUND = 100,
	ERR_FILE_PERMISSION = 101,
	ERR_FILE_EXTENSION = 102,
	ERR_FILE_EMPTY = 103,
	
	// Parse errors (200-299)
	ERR_PARSE_INVALID_IDENTIFIER = 200,
	ERR_PARSE_MISSING_VALUE = 201,
	ERR_PARSE_DUPLICATE_ELEMENT = 202,
	ERR_PARSE_INVALID_COLOR = 203,
	ERR_PARSE_INVALID_TEXTURE = 204,
	
	// Validation errors (300-399)
	ERR_VALIDATE_MAP_OPEN = 300,
	ERR_VALIDATE_MAP_CHARS = 301,
	ERR_VALIDATE_PLAYER_MISSING = 302,
	ERR_VALIDATE_PLAYER_MULTIPLE = 303,
	
	// Memory errors (400-499)
	ERR_MEMORY_ALLOC = 400
}	t_error_code;

// Error context structure
typedef struct s_error_context
{
	int		line_number;    // Line number where error occurred (-1 if N/A)
	char	*element;       // Element with error (NULL if N/A)
	char	*detail;        // Additional detail (NULL if N/A)
}	t_error_context;

// Initialize default error context
t_error_context	create_error_context(void);

// Set line number in error context
void	set_error_line(t_error_context *ctx, int line);

// Set element in error context
void	set_error_element(t_error_context *ctx, char *element);

// Set detail in error context
void	set_error_detail(t_error_context *ctx, char *detail);

// Central error handling function
int		handle_error(t_error_code code, t_error_context *ctx);

// Get error type from error code
t_error_type	get_error_type(t_error_code code);

// Get error message from error code
const char	*get_error_message(t_error_code code);

#endif