#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdatomic.h>
#include <pthread.h>
#include <stdbool.h>
#include <errno.h>
#include "rl_lock_library.h"

int main (int argc, char* argv[]){
  /*if(argc < 4){
    fprintf(stderr,"usage : %s shared_memory_object\n", argv[0]);
    exit(1);
  }*/
  rl_init_library();
  rl_all_files.nb_files = 0;
  /*rl_descriptor test = rl_open(argv[1],O_CREAT|O_RDWR);
  if (argc == 5){
    rl_init_library();
    if (strcmp(argv[4],"W")==0){
      struct flock fl = { .l_type = F_WRLCK, .l_whence = SEEK_SET, .l_start = atoi(argv[2]), .l_len = atoi(argv[3])};
      printf("pose de verrou d'écriture sur l'espace %ld - %ld sur fichier %s\n",fl.l_start,fl.l_len,argv[1]);
      int i  = rl_fcntl (test,F_SETLK,&fl);
      printf ("résultat : %d\n",i);
      i = 0;
      for (int j = 0; j < NB_LOCKS;j++){
        if (test.f->lock_table[j].nb_owners != 0){
          i++;
        }
      }
      printf("nb verrous sur %s : %d\n",argv[1],i);
    }else if (strcmp(argv[4],"R")==0){
      struct flock fl = { .l_type = F_RDLCK, .l_whence = SEEK_SET, .l_start = atoi(argv[2]), .l_len = atoi(argv[3])};
      printf("pose de verrou de lecture sur l'espace %ld - %ld sur fichier %s\n",fl.l_start,fl.l_len,argv[1]);
      int i  = rl_fcntl (test,F_SETLK,&fl);
      printf ("résultat : %d\n",i);
      i = 0;
      for (int j = 0; j < NB_LOCKS;j++){
        if (test.f->lock_table[j].nb_owners != 0){
          i++;
        }
      }
      printf("nb verrous sur %s : %d\n",argv[1],i);
    }else{
      fprintf(stderr,"%s n'est pas une commande reconnue\n", argv[4]);
      rl_close(test);
      exit(1);
    }
  }
  printf("rl_close sur %s\n",argv[1]);
  rl_close(test);
  int i = 0;
  i = 0;
  for (int j = 0; j < NB_LOCKS;j++){
    if (test.f->lock_table[j].nb_owners != 0){
      i++;
    }
  }
  printf("nb verrous sur %s : %d\n",argv[1],i);
  return 0;
} */
  rl_descriptor tester = rl_open("test",O_CREAT|O_RDWR);
  rl_open("test2",O_CREAT|O_RDWR);
  struct flock fl = { .l_type = F_RDLCK, .l_whence = SEEK_SET, .l_start = 0, .l_len = 100};
  printf("création verrou lecture sur test entre %ld et %ld\n",fl.l_start,fl.l_len);
  int i = rl_fcntl(tester,F_SETLK,&fl);
  printf("résultat: %d\n",i);
  
  print_all();
  
  fl.l_start = 20;
  fl.l_len = 30;
  printf("pose d'un verrou de lecture entre %ld et %ld sur test\n",fl.l_start,fl.l_len);
  i = rl_fcntl(tester,F_SETLK,&fl);
  printf("résultat: %d\n",i);
  i = 0;
  for (int j = 0; j < NB_LOCKS;j++){
    if (tester.f->lock_table[j].nb_owners != 0){
      i++;
    }
  }
  printf("nb verrous sur test: %d\n\n",i);
  print_all();
  fl.l_type = F_UNLCK;
  fl.l_start = 10;
  fl.l_len = 20;
  printf("déverrouillage sur test entre %ld et %ld\n",fl.l_start,fl.l_len);
  i = rl_fcntl(tester,F_SETLK,&fl);
  printf("résultat: %d\n",i);
  print_all();
  printf("\n");

  printf("Pose d'un verrou d'écriture sur le lock de lecture par le même processus\n");
  fl.l_type = F_WRLCK;
  fl.l_start = 30;
  fl.l_len = 100;
  i = rl_fcntl(tester,F_SETLK,&fl);
  printf("résultat : %d\n",i);
  print_all();
  printf("\n");

  printf("rl_dup2\n");
  rl_descriptor tester3 = rl_dup2(tester,10);
  print_all();
  printf("\n");

  printf("Pose d'un verrou de lecture sur le verrou d'écriture par le même processus\n");
  fl.l_type = F_RDLCK;
  i = rl_fcntl(tester,F_SETLK,&fl);
  printf("résultat : %d\n",i);
  print_all();
  printf("\n");
  pid_t pid = rl_fork();
  if(pid == -1){
    return 1;
  }else if (pid == 0){
    struct flock fl2 = {.l_type = F_WRLCK, .l_whence = SEEK_SET, .l_start = 30, .l_len = 100};
    printf("Pose d'un verrou d'écriture au même endroit que le verrou de lecture par un autre processus\n");
    i = rl_fcntl(tester,F_SETLK,&fl2);
    printf("résultat :%d\n",i);
    print_all();
    printf("\n");
    exit(0);

  }else{
    wait(NULL);
    /*printf("déverrouillage sur test avec un lock de longueur 0\n");
    fl.l_type = F_UNLCK;
    fl.l_start = 0;
    fl.l_len = 0;
    i = rl_fcntl(tester,F_SETLK,&fl);
    printf("résultat = %d\n",i);
    i = 0;
    for (int j = 0; j < NB_LOCKS;j++){
      if (tester.f->lock_table[j].nb_owners != 0){
        i++;
      }
    }
    printf("nb verrous sur test: %d\n\n",i);
    fl.l_type = F_RDLCK;
    printf("pose d'un verrou de lecture de longueur %d\n",0);
    i = rl_fcntl(tester,F_SETLK,&fl);
    printf("résultat = %d\n\n",i);
    
    for (int j = 0; j < NB_LOCKS;j++){
      if (tester.f->lock_table[j].nb_owners != 0){
        printf("tester.f->lock_table[%d].nb_owners = %ld\n",j,tester.f->lock_table[j].nb_owners);
        i++;
      }
    }
    printf("nb verrous sur test: %d\n\n",i);*/
    i = rl_close (tester);
    printf("rl_close sur test : %d verrous enlevés\n",i);
    print_all();
    printf("\n");
    struct flock fl3 = { .l_type = F_RDLCK, .l_whence = SEEK_SET, .l_start = 0, .l_len = 10};
    
    printf("Pose d'un verrou de lecture, après avoir fermé le descripteur\n");
      i = rl_fcntl(tester,F_SETLK,&fl3);
    printf("résultat : %d\n",i);
    print_all();
    printf("\n");
    printf("rl_close sur la duplication du descripteur\n");
    i = rl_close (tester3);
    printf("résultat : %d\n",i);
    print_all();
    printf("\n");
  return 0;
  }
}
