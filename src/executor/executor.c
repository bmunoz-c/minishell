/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrevin- <ltrevin-@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:50:26 by ltrevin-          #+#    #+#             */
/*   Updated: 2024/11/07 15:23:36 by ltrevin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Crear la lista de comandos
/*
 * un comando consta de:
 * 	char *cmd 	-> el texto literal del comando
 * 	char **args -> la lista de textos que recibe como argumento
 * 	int in_fd -> el fd que recoge de input
 * 	int out_fd -> el fd donde tiene que escribir
 * */
void create_cmd_list(){}

// recorre la lista de comandos y la ejecuta
void execute(t_data *data, t_cmd *cmds){

}

// gestiona las pipes (abre los procesos hijo)
void execute_pipe(){}

// BUILTINS
// Marcar una flag para saber si el comando es un builtin o no
void check_builtins(){}
// ejecuta la funcion q le toca
void execute_builtin(){}


//UTILS
//cerrar fd despues de ejecutaer
void close_fd(){}


