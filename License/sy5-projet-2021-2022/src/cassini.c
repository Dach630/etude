#include "print_reply.c"

const char usage_info[] = "\
   usage: cassini [OPTIONS] -l -> list all tasks\n\
      or: cassini [OPTIONS]    -> same\n\
      or: cassini [OPTIONS] -q -> terminate the daemon\n\
      or: cassini [OPTIONS] -c [-m MINUTES] [-H HOURS] [-d DAYSOFWEEK] COMMAND_NAME [ARG_1] ... [ARG_N]\n\
          -> add a new task and print its TASKID\n\
             format & semantics of the \"timing\" fields defined here:\n\
             https://pubs.opengroup.org/onlinepubs/9699919799/utilities/crontab.html\n\
             default value for each field is \"*\"\n\
      or: cassini [OPTIONS] -r TASKID -> remove a task\n\
      or: cassini [OPTIONS] -x TASKID -> get info (time + exit code) on all the past runs of a task\n\
      or: cassini [OPTIONS] -o TASKID -> get the standard output of the last run of a task\n\
      or: cassini [OPTIONS] -e TASKID -> get the standard error\n\
      or: cassini -h -> display this message\n\
\n\
   options:\n\
     -p PIPES_DIR -> look for the pipes in PIPES_DIR (default: /tmp/<USERNAME>/saturnd/pipes)\n\
";


int main(int argc, char * argv[]) {
  errno = 0;
  
  char * minutes_str = "*";
  char * hours_str = "*";
  char * daysofweek_str = "*";
  char * pipes_directory = NULL;
  
  uint16_t operation = CLIENT_REQUEST_LIST_TASKS;
  uint64_t taskid;
  
  int opt;
  char * strtoull_endp;
  while ((opt = getopt(argc, argv, "hlcqm:H:d:p:r:x:o:e:")) != -1) {
    switch (opt) {
    case 'm':
      minutes_str = optarg;
      break;
    case 'H':
      hours_str = optarg;
      break;
    case 'd':
      daysofweek_str = optarg;
      break;
    case 'p':
      pipes_directory = strdup(optarg);
      if (pipes_directory == NULL) goto error;
      break;
    case 'l':
      operation = CLIENT_REQUEST_LIST_TASKS;
      break;
    case 'c':
      operation = CLIENT_REQUEST_CREATE_TASK;
      break;
    case 'q':
      operation = CLIENT_REQUEST_TERMINATE;
      break;
    case 'r':
      operation = CLIENT_REQUEST_REMOVE_TASK;
      taskid = strtoull(optarg, &strtoull_endp, 10);
      if (strtoull_endp == optarg || strtoull_endp[0] != '\0') goto error;
      break;
    case 'x':
      operation = CLIENT_REQUEST_GET_TIMES_AND_EXITCODES;
      taskid = strtoull(optarg, &strtoull_endp, 10);
      if (strtoull_endp == optarg || strtoull_endp[0] != '\0') goto error;
      break;
    case 'o':
      operation = CLIENT_REQUEST_GET_STDOUT;
      taskid = strtoull(optarg, &strtoull_endp, 10);
      if (strtoull_endp == optarg || strtoull_endp[0] != '\0') goto error;
      break;
    case 'e':
      operation = CLIENT_REQUEST_GET_STDERR;
      taskid = strtoull(optarg, &strtoull_endp, 10);
      if (strtoull_endp == optarg || strtoull_endp[0] != '\0') goto error;
      break;
    case 'h':
      printf("%s", usage_info);
      return 0;
    case '?':
      fprintf(stderr, "%s", usage_info);
      goto error;
    }
  }
  if(pipes_directory == NULL){
    char *user = getenv("USER");
    pipes_directory = malloc(PATH_MAX);
    strcat(pipes_directory, "/tmp/");
    strcat(pipes_directory, user);
    strcat(pipes_directory, "/saturnd/pipes");
  }
   
  char * request_pipe = malloc(PATH_MAX);
  request_pipe[0] = 0;
  strcat(request_pipe, pipes_directory);
  strcat(request_pipe, "/saturnd-request-pipe");
  char * reply_pipe = malloc(PATH_MAX);
  reply_pipe[0] = 0;
  strcat(reply_pipe, pipes_directory);
  strcat(reply_pipe, "/saturnd-reply-pipe");

  int fd = open(request_pipe, O_WRONLY);
  if(fd == -1){
    perror("open");
    goto error;
  }
  uint16_t op = htobe16(operation);
  int a = write(fd, &op, sizeof(u_int16_t));
  if(a != sizeof(u_int16_t)){
    perror("write op");
    goto error;
  }
  
  if(operation == CLIENT_REQUEST_CREATE_TASK){
    struct timing *t = malloc(sizeof(struct timing));
    timing_from_strings(t, minutes_str, hours_str, daysofweek_str);
    a = write(fd, t, sizeof(struct timing));
    if(a != sizeof(struct timing)){
      perror("write timing");
      goto error;
    }
    free(t);
    uint32_t c = (uint32_t) htobe32(argc - optind) ;
    a = write(fd, &c, sizeof(uint32_t));
    if(a != sizeof(uint32_t)){
      perror("write argc");
      goto error;
    }

    for(int i = optind; i<argc; i++){  
      uint32_t longueur = htobe32(strlen(argv[i]));
      a = write(fd, &longueur, sizeof(longueur));
      if(a != sizeof(longueur)){
	perror("write argvs");
	goto error;
      }
	
      a = write(fd, argv[i], strlen(argv[i]));
      if(a != strlen(argv[i])){
	perror("write argvs");
	goto error;
      }
    }
  
  }
  
  else if(operation==CLIENT_REQUEST_REMOVE_TASK||
    operation == CLIENT_REQUEST_GET_TIMES_AND_EXITCODES ||
	  operation == CLIENT_REQUEST_GET_STDERR ||
	  operation == CLIENT_REQUEST_GET_STDOUT){
    taskid = htobe64(taskid);
    a = write(fd, &taskid, sizeof(uint64_t));
    if(a != sizeof(uint64_t)) {
      perror("write taskid");
      goto error;
    }
  }
    
  close(fd);
  free(pipes_directory);
  free(request_pipe);
  free(reply_pipe);

  
  if (print_reply(reply_pipe, operation) == 0) return EXIT_SUCCESS;
  else return 1;

 error:
  if (errno != 0) perror("main");
  free(pipes_directory);
  pipes_directory = NULL;
  return EXIT_FAILURE;
}

