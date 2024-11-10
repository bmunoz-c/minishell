function run_executor(token_list):
    command_groups = group_commands(token_list)
    
    if command_groups.length == 1:
        run_single_command(command_groups[0])
    else:
        run_pipeline(command_groups)

function group_commands(token_list):
    // Split the token list into separate command groups based on pipes or semicolons
    command_groups = []
    current_group = []
    
    for token in token_list:
        if token.content is a pipe or semicolon:
            command_groups.append(current_group)
            current_group = []
        else:
            current_group.append(token)
    
    if current_group is not empty:
        command_groups.append(current_group)

    return command_groups

function run_single_command(command_group):
    if is_builtin_command(command_group):
        handle_builtin(command_group)
        return

    pid = fork()
    if pid == 0:  // In the child process
        setup_io_redirection(command_group)
        command = build_command_structure(command_group)
        execve(command.path, command.args, command.env)
        exit_on_error()  // If execve fails, terminate child process
    else if pid > 0:  // In the parent process
        wait_for_child(pid)
    else:
        log_error("Failed to fork")

function run_pipeline(command_groups):
    pipe_fds = []

    for i in range 0 to command_groups.length:
        if i < command_groups.length - 1:  // Not the last command
            create_pipe(pipe_fds)

        pid = fork()
        if pid == 0:  // In the child process
            if i > 0:  // If not the first command, set input from previous pipe
                dup2(pipe_fds[i-1][0], STDIN_FILENO)
                close(pipe_fds[i-1][1])
            if i < command_groups.length - 1:  // If not the last command, set output to next pipe
                dup2(pipe_fds[i][1], STDOUT_FILENO)
                close(pipe_fds[i][0])

            setup_io_redirection(command_groups[i])
            command = build_command_structure(command_groups[i])
            execve(command.path, command.args, command.env)
            exit_on_error()  // Terminate if execve fails
        else if pid > 0:  // In the parent process
            if i > 0:
                close(pipe_fds[i-1][0])
                close(pipe_fds[i-1][1])
            wait_for_child(pid)
        else:
            log_error("Failed to fork")

function setup_io_redirection(command_group):
    for token in command_group:
        if token is an input redirection:
            fd_in = open(token.content, O_RDONLY)
            if fd_in == -1:
                log_error("Failed to open input file")
            dup2(fd_in, STDIN_FILENO)
            close(fd_in)
        else if token is an output redirection:
            fd_out = open(token.content, O_WRONLY | O_CREAT | O_TRUNC, 0644)
            if fd_out == -1:
                log_error("Failed to open output file")
            dup2(fd_out, STDOUT_FILENO)
            close(fd_out)

function handle_builtin(command_group):
    // Execute built-in command based on the first token in the group
    first_token = command_group[0]
    switch first_token.content:
        case "cd":
            change_directory(command_group)
        case "export":
            set_env_var(command_group)
        case "unset":
            unset_env_var(command_group)
        case "exit":
            exit_shell(command_group)
        // Add other built-ins as needed

function build_command_structure(command_group):
    // Construct the command structure (path, args, env) from tokens
    command.path = find_command_path(command_group)
    command.args = extract_command_args(command_group)
    command.env = get_current_env()
    return command
