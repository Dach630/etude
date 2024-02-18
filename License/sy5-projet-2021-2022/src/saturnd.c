#include "cassini.h"

void mk_saturnd_dir(char *saturnd_directory, char *user,char *pipes_directory,char *tasks_directory,char *request_pipe, char *reply_pipe)
{
  strcat(saturnd_directory, "/tmp/");
  strcat(saturnd_directory, user);
  mkdir(saturnd_directory, S_IRWXU);
  strcat(saturnd_directory, "/saturnd");
  mkdir(saturnd_directory, S_IRWXU);
  strcat(pipes_directory, saturnd_directory);
  strcat(pipes_directory, "/pipes");
  mkdir(pipes_directory, S_IRWXU);
  strcat(tasks_directory, saturnd_directory);
  strcat(tasks_directory, "/tasks");
  mkdir(tasks_directory, S_IRWXU);
  strcat(request_pipe, pipes_directory);
  strcat(request_pipe, "/saturnd-request-pipe");
  strcat(reply_pipe, pipes_directory);
  strcat(reply_pipe, "/saturnd-reply-pipe");
  mkfifo(request_pipe, 0666);
  mkfifo(reply_pipe, 0666);
}

int rmtree(const char path[]){
  size_t path_len;
  char *full_path;
  DIR *dir;
  struct stat stat_path, stat_entry;
  struct dirent *entry;
  stat(path, &stat_path);
  
  if (S_ISDIR(stat_path.st_mode) == 0) return -1;
  if ((dir = opendir(path)) == NULL) return -1;
  
  path_len = strlen(path);
  while ((entry = readdir(dir)) != NULL){
    if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
      continue;
    full_path = calloc(path_len + strlen(entry->d_name) + 1, sizeof(char));
    strcpy(full_path, path);
    strcat(full_path, "/");
    strcat(full_path, entry->d_name);
    stat(full_path, &stat_entry);
    if (S_ISDIR(stat_entry.st_mode) != 0){
      rmtree(full_path);
      continue;
    }
    unlink(full_path);
    free(full_path);
  }
  rmdir(path);
  closedir(dir);
  return 0;
}

int count_nbrDir(const char path[]){
    size_t path_len;
    char* full_path;
    DIR* dir;
    struct stat stat_path, stat_entry;
    struct dirent* entry;

    stat(path, &stat_path);

    if (S_ISDIR(stat_path.st_mode) == 0) return 0;
    if ((dir = opendir(path)) == NULL) return 0;
    
    int res = 0;
    while ((entry = readdir(dir)) != NULL) {
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
            continue;
        res++;
    }
    return res;
}

int main()
{
  //Creation de fichiers
  char *saturnd_directory = malloc(PATH_MAX);
  char *user = getenv("USER");
  char *pipes_directory = malloc(PATH_MAX);
  char *tasks_directory = malloc(PATH_MAX);
  char *request_pipe = malloc(PATH_MAX);
  char *reply_pipe = malloc(PATH_MAX);
  char *tache = malloc(PATH_MAX);

  mk_saturnd_dir(saturnd_directory, user,pipes_directory,tasks_directory,request_pipe, reply_pipe);
  
  int fd_request = open(request_pipe, O_RDWR);
  int fd_reply = open(reply_pipe, O_RDWR);

  struct timing *time = malloc(sizeof(struct timing));
  char *idtache = malloc(10);
  uint32_t longueur;

  int fd_write;
  uint16_t reponse;
  char buf[256];

  int out;
  int ex;
  uint32_t len_str;
  uint16_t exCode;
  char* str;
  char* expath;
  char* tmp;
  char* tmp_ssdir;
  DIR *dir;
  DIR* sous_dir;
  struct dirent* dire;
  uint64_t taskid;
  uint32_t nbr_arg;
  int tmp_open;
  int nb_task;

  int r = fork();
  switch(r) {
  case -1 :
    perror("fork");
  case 0 : // fils
    setsid();
    while(1){
      uint16_t op;
      int a = read(fd_request, &op, sizeof(uint16_t));
      uint32_t nbr_arg;

      switch (htobe16(op)){	
      case CLIENT_REQUEST_LIST_TASKS: //l'utilisation de ls arrete le demon
	reponse = htobe16(SERVER_REPLY_OK);
	write(fd_reply, &reponse, sizeof(uint16_t));
	nb_task = count_nbrDir(tache);
	uint32_t nbr_arg = (uint32_t) htobe32(nb_task);
	write(fd_reply, &nbr_arg, sizeof(uint16_t));

	dir = opendir(tache);
	strcat(tache, "/");
	while ((dire = readdir(dir)) != NULL) {
	  if (!strcmp(dire->d_name, ".") || !strcmp(dire->d_name, "..")) continue;

	  taskid = atoi(dire -> d_name);
	  write(fd_reply, &taskid, sizeof(uint64_t));

	  strcpy(tmp, tache);
	  printf("%s\na", tmp);
	  strcat(tmp, dire-> d_name);
	  strcat(tmp, "/");
	  strcpy(tmp_ssdir, tmp);
	  strcat(tmp_ssdir, "/timing");

	  tmp_open = open(tmp_ssdir, O_RDONLY);
	  read(tmp_open, &time, sizeof(struct timing));
	  write(fd_reply, &time, sizeof(struct timing));
	  close(tmp_open);

	  strcat(tmp, "/argument");
	  tmp_open = open(tmp, O_RDONLY);
	  struct stat sb;
	  stat(tache, &sb);
	  len_str = htobe32(sb.st_size);
	  write(fd_reply, &len_str, sizeof(uint32_t));
	  str = malloc(sb.st_size);
	  read(tmp_open, &str, sb.st_size);
	  write(fd_reply, &str, sb.st_size);
	  free(str);
	  close(tmp_open);
	  closedir(sous_dir);
	}
	closedir(dir);
	break;

      case CLIENT_REQUEST_CREATE_TASK:
	r = fork();
	switch (r){
	case -1:
	  perror("create fork");
	  
	case 0 :

	  printf("%d\n", getpid());
	  sprintf(idtache, "%d", getpid());
	  strcat(tache, "/");
	  strcat(tache, idtache);
	  mkdir(tache, S_IRWXU);

	  
	  read(fd_request, &time, sizeof(struct timing));
	  
	  fd_write = open(strcat(tache, "/time"), O_WRONLY | O_CREAT, 0666);
	  write(fd_write, &time, sizeof(struct timing));
	  close(fd_write);
	  
	  strcpy(tache, tasks_directory);
	  strcat(tache, "/");
	  strcat(tache, idtache);

	  fd_write = open(strcat(tache, "/arguments"), O_WRONLY | O_APPEND | O_CREAT, 0666);
	  read(fd_request, &nbr_arg, sizeof(uint32_t));
	  write(fd_write, &nbr_arg, sizeof(uint32_t));
	  int nbr = (int) be32toh(nbr_arg);
	  
	  for(int i = 0; i < nbr; i++){
	    read(fd_request, &longueur, sizeof(uint32_t));
	    int lg = (int) be32toh(longueur);
	    char *chaine = malloc(lg);
	    read(fd_request, chaine, lg);
	    write(fd_write, &longueur, sizeof(uint32_t));
	    write(fd_write, chaine, lg);
	    free (chaine);
	  }
	  close(fd_write);
	  reponse = htobe16(0x4f4b);
	  uint64_t id = htobe64(getpid());
	  write(fd_reply, &reponse, sizeof(uint16_t));
	  write(fd_reply, &id, sizeof(uint64_t));
	  return 0;
	  //ajouter execution et creation de stdout stderr
	default:
	  break;
	}
	break;
	
      case CLIENT_REQUEST_REMOVE_TASK:
        a = read(fd_request, &taskid, sizeof(uint64_t));
        snprintf(buf, sizeof buf, "%" PRIu64, htobe64(taskid));

        strcpy(tache, tasks_directory);
        strcat(tache, "/");
        strcat(tache, buf);

        a = rmtree(tache);
        if (a == 0)
	  {
	    reponse = htobe16(SERVER_REPLY_OK);
	    write(fd_reply, &reponse, sizeof(uint16_t));
	  }
        else
	  {
	    reponse = htobe16(SERVER_REPLY_ERROR);
	    write(fd_reply, &reponse, sizeof(uint16_t));
	    reponse = htobe16(0x4e46);
	    write(fd_reply, &reponse, sizeof(uint16_t));
	  }

        break;
	
      case CLIENT_REQUEST_GET_TIMES_AND_EXITCODES:
	break;
	
      case CLIENT_REQUEST_TERMINATE:
	reponse = htobe16(0x4f4b);
	write(fd_reply, &reponse, sizeof(uint16_t));
	close(fd_reply);
	free(saturnd_directory);
	free(pipes_directory);
	free(tasks_directory);
	free(request_pipe);
	free(reply_pipe);
	free(tache);
	free(idtache);
	free(time);

	return 0;
	break;
	
      case CLIENT_REQUEST_GET_STDOUT:
        a = read(fd_request, &taskid, sizeof(uint64_t));
        snprintf(buf, sizeof buf, "%" PRIu64, htobe64(taskid));
        strcpy(tache, tasks_directory);
        strcat(tache, "/");
        strcat(tache, buf);

        dir = opendir(tache);

        if (dir == NULL){
          reponse = htobe16(SERVER_REPLY_ERROR);
          write(fd_reply, &reponse, sizeof(uint16_t));
          reponse = htobe16(SERVER_REPLY_ERROR_NOT_FOUND);
          write(fd_reply, &reponse, sizeof(uint16_t));
          closedir(dir);
        }
        else{
          strcpy(expath, tache);
          strcat(expath, "/exitcode");
          ex = open(tache, O_RDONLY | O_NONBLOCK);
          read(ex, &exCode, sizeof(uint16_t));

          if ((htobe16(exCode)) == 0){
            reponse = htobe16(SERVER_REPLY_OK);
            write(fd_reply, &reponse, sizeof(uint16_t));
            struct stat sb;

            if (stat(tache, &sb) == -1){
              perror("stat");
              closedir(dir);
              close(out);
              exit(EXIT_FAILURE);
            }
            len_str = htobe32(sb.st_size);
            write(fd_reply, &len_str, sizeof(uint32_t));

            strcat(tache, "/stdout");
            out = open(tache, O_RDONLY);
            str = malloc(sb.st_size);
	    read(out, &str, sb.st_size);
            write(fd_reply, &str, sb.st_size);
	    
            close(out);
          }

          else{
            reponse = htobe16(SERVER_REPLY_ERROR);
            write(fd_reply, &reponse, sizeof(uint16_t));
            reponse = htobe16(SERVER_REPLY_ERROR_NEVER_RUN);
            write(fd_reply, &reponse, sizeof(uint16_t));
          }
          close(ex);
        }
        closedir(dir);	
	break;
	
      case CLIENT_REQUEST_GET_STDERR:			
	break;
      }
      sleep(1);
    }
    break;
  default : // père
    close(fd_reply);
    free(saturnd_directory);
    free(pipes_directory);
    free(tasks_directory);
    free(request_pipe);
    free(reply_pipe);
    free(tache);
    free(idtache);
    free(time);
    return 0;
    
  }
}
