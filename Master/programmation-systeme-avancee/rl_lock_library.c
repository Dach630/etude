//CHENG Daniel 21954618
//ROMELE Gaspard 21950004

#include "rl_lock_library.h"

//genere le nom du shared memory object (partie 5.3.1 du sujet)
char* generateSharedMemoryObjectName (dev_t st1,ino_t st2) {
  char* buffer;
  buffer = (char*) malloc (sizeof(char)* 100);
  if(buffer == NULL){
        perror("malloc");
        exit(1);
  }else{
    sprintf (buffer,"/f_%ld_%ld",st1,st2);
    return buffer;
  }
}

int initialiser_mutex(pthread_mutex_t *pmutex){
  pthread_mutexattr_t mutexattr;
  int code;
  if((code = pthread_mutexattr_init(&mutexattr))!= 0)	return code;
  if((code = pthread_mutexattr_setpshared(&mutexattr,PTHREAD_PROCESS_SHARED))!= 0) return code;
  code = pthread_mutex_init(pmutex, &mutexattr);
  return code;
}

int initialiser_cond(pthread_cond_t *pcond){
  pthread_condattr_t condattr;
  int code;
  if((code = pthread_condattr_init(&condattr))!= 0) return code;
  if((code = pthread_condattr_setpshared(&condattr,PTHREAD_PROCESS_SHARED))!= 0) return code;
  code = pthread_cond_init(pcond, &condattr); 
  return code;
}	

void thread_error(const char *file, int line, int code, char *txt){
  if(txt != NULL){
    fprintf(stderr,"[%s] in file %s in line %d : %s\n",txt,file,line,strerror(code ));
  }else{
    fprintf(stderr,"in file %s in line %d : %s\n",file,line,strerror(code));
    exit(1);
  }
}

rl_descriptor rl_open (const char *path, int oflag, ...){
  bool new_shm = true;
  rl_descriptor descriptor;
  int fd = open (path,oflag);
  descriptor.d = fd;
  if (fd == -1) {
    perror("open");
    exit(1);
  }
  struct stat buf;
  int j = fstat(fd,&buf);
  if(j == -1){
    perror("fstat");
    exit(1);
  }
  char *shm_name = generateSharedMemoryObjectName(buf.st_dev,buf.st_ino);
  unlink(path);
  fd = shm_open(shm_name,oflag,S_IWUSR|S_IRUSR);
  if( fd >= 0 ){
    if(ftruncate(fd, sizeof(rl_descriptor)) < 0){
      perror("ftruncate");
      exit(1);
    }
  }else if( fd < 0 && errno == EEXIST ){
    fd = shm_open(shm_name,O_RDWR,S_IWUSR|S_IRUSR);
    if( fd < 0 ){
      perror("shm_open existing object");
      exit(1);
    }
    new_shm = false;
  }else{
    perror("shm_open");
    exit(1);
  } 
  rl_open_file * obj = mmap(0, sizeof(rl_open_file),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0); 
  if(new_shm){
    obj->lock_table = (rl_lock *) malloc (NB_LOCKS* sizeof(rl_lock));
    for (int i = 0; i < NB_LOCKS; i++){
      rl_lock a;
      a.starting_offset = -1;
      a.len = -1;
      a.next_lock = -2;
      a.nb_owners = 0;
      //obj->lock_table[i] =(rl_lock) malloc (sizeof (rl_lock));
      obj->lock_table[i] = a;
    }
    obj->first = -2;
    descriptor.f = obj;
    rl_all_files.tab_open_files[rl_all_files.nb_files] = obj;
    rl_all_files.nb_files++;

  }
  printf ("rl_open success on %s\n",path);
  return descriptor;
}

int rl_close(rl_descriptor lfd) {
    int indice = lfd.f->first;
    int pid = (int) getpid();
    if (indice == -2) {
        return 0;
    }
    int val = lfd.d; // valeur a fermer
    int cl = 1;
    //close(val);
    rl_lock* lock_tableTMP = lfd.f->lock_table;
    int nbsupp = 0;//nombre de supression
    int isfirst = 1;
    int prev = 0;
    while (indice >= 0) {
        int id = 0;
         //printf("lock_tableTMP[indice].nb_owners = %ld\n",lock_tableTMP[indice].nb_owners);
        while (id < lock_tableTMP[indice].nb_owners) {
            if ((lock_tableTMP[indice].lock_owners[id]).des == val) {
                if ((int)(lock_tableTMP[indice].lock_owners[id]).proc == pid) {
                    lock_tableTMP[indice].lock_owners[id] = lock_tableTMP[indice].lock_owners[(lock_tableTMP[indice].nb_owners) - 1];
                    //lock_tableTMP[indice].lock_owners[(lock_tableTMP[indice].nb_owners) - 1];
                    lock_tableTMP[indice].nb_owners -= 1;
                    nbsupp++; 
                }else{
                  cl = 0;
                }
            }
            else {
                id++;
            }
        }
        if (lock_tableTMP[indice].nb_owners == 0) {
            if (isfirst == 1) {
                if (lock_tableTMP[indice].next_lock == -1) {
                    lfd.f->first = -2;
                }else{
                    lfd.f->first = lock_tableTMP[indice].next_lock;
                }
            }
            else { // isfirst = 0 donc on a un lock non vide avant
                lock_tableTMP[prev].next_lock = lock_tableTMP[indice].next_lock;
            }
            lock_tableTMP[indice].m->libre = true;
            int code = 0;
            if((code = pthread_mutex_unlock(&lock_tableTMP[indice].m->mutex))!= 0) thread_error(__FILE__ , __LINE__ , code, "mutex_lock");
            prev = indice;
            indice = lock_tableTMP[indice].next_lock;
            lock_tableTMP[prev].next_lock = -2;
        }
        else {
            isfirst = 0;
            prev = indice;
            indice = lock_tableTMP[indice].next_lock;
        }
    }
    if(cl == 1){
      close(val);
    }
    return nbsupp;
}

owner * init_lfd_owner (rl_descriptor lfd){
  owner * lfd_owner = (owner *) malloc (sizeof (owner));
  lfd_owner->proc = getpid();
  lfd_owner->des = lfd.d; 
  return lfd_owner;
}

bool owner_equal_lfd_owner (owner lfd_owner,owner ow){
  if (lfd_owner.proc == ow.proc && lfd_owner.des == ow.des) return true;
  return false;
}

int lfd_owner_in_lock_owners (owner lfd_owner,rl_lock lock){
  int i = 0;
  while(i < NB_OWNERS) {
    if (owner_equal_lfd_owner(lfd_owner,lock.lock_owners[i])){
      return i;
    }
    i++;
  }
  return -1;
}

bool premier_element_lock_table (rl_lock * tab){
  int j = 0;
  while (j < NB_LOCKS){
    if (tab[j].nb_owners != 0) return j;
    j++; 
  }
  return -1;
}

int already_locked (int pos, off_t start, off_t length, rl_lock * fl, pid_t pid ){
  //trouver si un verrou est deja pose sur une section ou sur l'ensemble de l'emplacement ou l'on voudrait poser un nouveau verrou
  int i = pos;
  while (i < NB_LOCKS){
    if (fl[i].nb_owners != 0){
      if(((fl[i].starting_offset <= length && fl[i].len >= start) || (fl[i].starting_offset > start && fl[i].len < length)) && fl[i].starting_offset != -1){
        //printf("already locked %d\n",i);
        return i;      
      }
      i++;
    }else{
      i++;
    }
  }
  //printf("pas de verrou sur l'espace %ld - %ld \n",start,length);
  return -1;
}

int * lfd_owner_belongs_to_lock_tab (owner lfd_owner,rl_open_file lfd_file, off_t start, off_t len){
  static int r[2];
  int i = 0;
  while(i < NB_LOCKS){
  	int k;
  	if (len == 0) {
	    k = already_locked(0,start,1000,&lfd_file.lock_table[i],getpid());
	 }else{
	 	k = already_locked(0,start,len,&lfd_file.lock_table[i],getpid());
	 }
    int j = lfd_owner_in_lock_owners(lfd_owner,lfd_file.lock_table[k]);
    if (j != -1){
      r[0] = k;
      r[1] = j;
      return r; 
    }
    i++;
  }
  r[0] = -1;
  r[1] = -1;
  return r;
}

owner * delete_lock_owner (owner * current_owners,int i){
  //efface le propriétaire à la position i dans le owner * de rl_lock et décale tous les éléments pour combler le trou 
  while (i < NB_OWNERS-1){
    current_owners[i].proc = current_owners[i+1].proc;
    current_owners[i].des = current_owners[i+1].des;
    i++;
  }
  current_owners[i].proc = -1;
  current_owners[i].des = -1;
  return current_owners;
}

rl_lock * delete_lock (rl_lock * current_locks,int i){
  //efface un verrou quand un seul propriétaire existe et qu'on l'enlève du verrou
  for (int j = 0; j < NB_LOCKS ; j++){
    if (current_locks[j].next_lock == i){
      //remplace le next_lock des lock qui avaient le lock qu'on supprime en next_lock
      current_locks[j].next_lock = current_locks[i].next_lock;
    }else if (j == i){  
      current_locks[j].next_lock = -2;
      current_locks[j].starting_offset = -1;
      current_locks[j].len = -1;
      current_locks[j].nb_owners = 0;
      owner* updated_owners = delete_lock_owner(current_locks[j].lock_owners, 0);
      memcpy(current_locks[j].lock_owners, updated_owners, sizeof(owner) * NB_OWNERS);
      current_locks[j].m->libre = true;
      int code = 0;
      if((code = pthread_mutex_unlock(&current_locks[j].m->mutex))!= 0) thread_error(__FILE__ , __LINE__ , code, "mutex_lock");
    }
  }
  return current_locks;
}

//regarde si la table de locks est pleine 
bool lock_table_full (rl_lock * current_locks ){
  for (int i = 0; i < NB_LOCKS; i++){
    if (current_locks[i].nb_owners == 0){
      return false;
    }
  }
  return true;
}

rl_lock * pose_lock (rl_lock * current_locks , rl_lock newlock){
  //pose un nouveau verrou dans le lock_table
  //si la table est remplie on renvoit une erreur 
  if (lock_table_full(current_locks)){
    perror ("file lock_table full \n");
    exit(1);
  }
  int i = 0;
  int freespace = 0;
  int pos_freespace = -1;
  //On lit la table des locks jusqu'à ce qu'on ait un starting_offset inférieur ou qu'on ait plus aucun élément 
  while (current_locks[i].starting_offset < newlock.starting_offset && i < NB_LOCKS){
    if (current_locks[i].next_lock == -2){
      freespace = i;
      pos_freespace = freespace;
      while (current_locks[freespace].next_lock == -2 && freespace < NB_LOCKS){
        freespace++;
      }
    }
    if (freespace == NB_LOCKS){
      //si on ne trouve aucun lock de i jusqu'à la fin de lock_table on peut placer le lock à i
      newlock.next_lock = -1;
      current_locks[pos_freespace] = newlock;
      current_locks[pos_freespace].next_lock = -1;
      i--;
      if(i >= 0){
        while (i >= 0 && current_locks[i].nb_owners == 0){
          i--;
        }
        if (current_locks[i].nb_owners != 0 && i != pos_freespace){
          current_locks[i].next_lock = pos_freespace;
        }
      }
      printf("lock posé position %d sur l'espace %ld - %ld \n",pos_freespace,newlock.starting_offset,newlock.len);
      return current_locks;
    }
    if (freespace>i){
      i=freespace;
    }
    i++;
  }
  //si l'on a pas trouve d'espace libre, cela signifie qu'on est d'abord tombe sur un lock avec un starting_offset superieur
  //on sait que la table a au moins un espace libre, on en trouvera donc toujours un plus loin dans la table
  if (pos_freespace == -1){
    int a = i+1;
    //on décale tous les éléments avant cet espace libre vers la droite pour poser le nouveau lock
    while (current_locks[a].nb_owners != 0){
     a++;  
    }
    for (int b = a; b >= i;b--){
      current_locks[b] = current_locks[b-1];
      if(b>i && b<a){
        current_locks[b].next_lock = b+1;
      }
    }
    current_locks[i] = newlock;
    current_locks[i].next_lock = i+1;
    printf("lock posé position %d après décalage d'éléments à droite \n",i);
    return current_locks;
  }
  //si on a un emplacement libre avant on regarde s'il est juste avant le lock au starting_offset supérieur
  if (i-1 == freespace){
    newlock.next_lock = i;
    current_locks[pos_freespace] = newlock;
    if (pos_freespace > 0){
      current_locks[pos_freespace-1].next_lock = pos_freespace;
    }
    printf("lock posé position %d, on a trouvé une position libre avant lock supérieur \n",pos_freespace);
    return current_locks;
  }
  //sinon on décale tous les locks d'une position vers la gauche jusqu'à l'espace libre 
  int a = i-2;
  while (current_locks[a].nb_owners!=0){
    a--;
  }
  for (int b = a; b < i-1; b++){
    current_locks[b] = current_locks[b+1];
    if (b>a){
      current_locks[b].next_lock = b-1;
    }
  }
  newlock.next_lock = i;
  current_locks[i-1] = newlock;
  return current_locks;
}

rl_lock * enleve_lock_ou_owner (int a,int b,rl_descriptor lfd){
  //printf("enleve lock a: %d\n",a);
  rl_lock lock = lfd.f->lock_table[a];
  if (lock.nb_owners == 1){
    printf("un seul owner sur le lock en position %d, on supprime le lock\n",a);
    rl_lock * updated_lock = delete_lock(lfd.f->lock_table,a);
    memcpy(lfd.f->lock_table, updated_lock, sizeof(lock) * NB_LOCKS);
    return lfd.f->lock_table;
    //lfd.f->first = premier_element_lock_table (lfd.f->lock_table);
  }else if (lock.nb_owners > 1){
    int i = 0;
    while (i < lock.nb_owners && i != -1){
      owner ow;
      ow.des = lfd.d;
      ow.proc = (int) getpid();
      if (owner_equal_lfd_owner(lock.lock_owners[i],ow)){
        printf("plusieurs owners sur le lock %d\n",a);
        owner* updated_owners = delete_lock_owner(lock.lock_owners,b);
        lfd.f->lock_table[a].nb_owners--;
        memcpy(lfd.f->lock_table[a].lock_owners,updated_owners,sizeof(owner) * NB_OWNERS);
        i--;
      }else{
        i++;
      }
    }
    //memcpy(lfd.f->lock_table->lock_owners, updated_owners, sizeof(owner) * NB_OWNERS); 
    return lfd.f->lock_table;
  }else{
    return lfd.f->lock_table;
  }
}

int rl_fcntl (rl_descriptor lfd, int cmd, struct flock *lck){
owner * lfd_owner = init_lfd_owner(lfd);
  if (cmd == F_SETLK) {
    struct stat buf;
    int status = fstat(lfd.d, &buf);
    if (status == -1){
      perror("fstat");
      return -1;
    }
    if (lck -> l_start < 0 || lck-> l_len < 0){
      perror("dimensions du lock impossible\n");
      return (-1);
    }
    int *i = lfd_owner_belongs_to_lock_tab (*lfd_owner,*lfd.f, lck -> l_start, lck -> l_len);
    rl_lock lock = lfd.f->lock_table[i[0]];
    if (lck->l_type == F_UNLCK){
      if (i[0] != -1){ // verifie que lfd_owner a un lock dans lock_table
        printf("lfd_owner a un lock dans le lock_table du rl_open_file\n");
        if (lck -> l_len == 0){  //si lck -> l_len == 0 on deverouille tous les locks que lfd_owner a pose sur le smo
          printf("on déverrouile tous les locks de ce lfd_owner posés sur le rl_open_file\n");
          lck -> l_start = 0;
          lck -> l_len = 1000;
          while (i[0] != -1){ 
            lfd.f->lock_table = enleve_lock_ou_owner(i[0],i[1],lfd);
            i = lfd_owner_belongs_to_lock_tab (*lfd_owner, *lfd.f , lck -> l_start, lck -> l_len);
            lock = lfd.f->lock_table[i[0]];
          }
          return 0;
        }else{         
          int a = already_locked(0,lck->l_start,lck->l_len,lfd.f->lock_table,getpid());
          //int z = lfd_owner_in_lock_owners(*lfd_owner,lfd.f->lock_table[a]);
          while (a != -1){
            //if (z != 0){
              printf("On a encore un verrou entre %ld et %ld sur ce rl_open_file\n",lck->l_start,lck->l_len);
              i = lfd_owner_belongs_to_lock_tab (*lfd_owner, *lfd.f , lck -> l_start, lck -> l_len);
              if (i[0] != -1){
                printf("Le lock_owner est dans le verrou que l'on veut déverrouiller sur ce rl_open_file\n");
                if (lfd.f->lock_table[a].starting_offset >= lck -> l_start && lfd.f->lock_table[a].len <= lck -> l_len){ //cas où tout le verrou est efface 
                  printf("suppression de l'entièrete du verrou \n");
                  lfd.f->lock_table = enleve_lock_ou_owner(i[0],i[1],lfd);
                  if (lfd.f->lock_table[a].nb_owners == 0){
                    a = already_locked(a+1,lck->l_start,lck->l_len,lfd.f->lock_table,getpid());
                  }else{
                    a = already_locked(a+1,lck->l_start,lck->l_len,lfd.f->lock_table,getpid()); 
                  }
                  //z = lfd_owner_in_lock_owners(*lfd_owner,lfd.f->lock_table[a]);
                }else if (lfd.f->lock_table[a].starting_offset >= lck -> l_start && lfd.f->lock_table[a].len >= lck ->l_len){ //cas où tout le debut du verrou est efface mais pas la fin
                  printf("suppression du début du lock,de %ld à %ld\n",lfd.f->lock_table[a].starting_offset,lck ->l_len); 
                  rl_lock newlock;
                  newlock.nb_owners = 1;
                  newlock.type = lfd.f->lock_table[a].type;
                  newlock.starting_offset = lck -> l_len +1;
                  newlock.len = lfd.f->lock_table[a].len;
                  newlock.lock_owners[0] = *lfd_owner;
                  newlock.m = lock.m;
                  lfd.f->lock_table = enleve_lock_ou_owner(i[0],i[1],lfd);
                  if (lfd.f->lock_table[a].nb_owners == 0){
                    a = already_locked(a+1,lck->l_start,lck->l_len,lfd.f->lock_table,getpid());
                  }else{
                    a = already_locked(a+1,lck->l_start,lck->l_len,lfd.f->lock_table,getpid()); 
                  }
                  lfd.f->lock_table = pose_lock(lfd.f->lock_table,newlock);
                  lfd.f->first = premier_element_lock_table (lfd.f->lock_table);
                  //z = lfd_owner_in_lock_owners(*lfd_owner,lfd.f->lock_table[a]);
                }else if (lfd.f->lock_table[a].starting_offset <= lck -> l_start && lfd.f->lock_table[a].len <= lck ->l_len){ // cas où la fin du verrou est effacé mais pas le début 
                  printf("suppression de la fin du lock,de %ld à %ld\n",lck->l_start,lfd.f->lock_table[a].len); 
                  rl_lock newlock;
                  newlock.nb_owners = 1;
                  newlock.type = lfd.f->lock_table[a].type;
                  newlock.starting_offset = lfd.f->lock_table[a].starting_offset;
                  newlock.len = lck->l_start - 1;
                  newlock.lock_owners[0] = *lfd_owner;
                  newlock.m = lfd.f->lock_table[a].m;
                  lfd.f->lock_table = enleve_lock_ou_owner(i[0],i[1],lfd);
                   if (lfd.f->lock_table[a].nb_owners == 0){
                      a = already_locked(a+1,lck->l_start,lck->l_len,lfd.f->lock_table,getpid());
                    }else{
                      a = already_locked(a+1,lck->l_start,lck->l_len,lfd.f->lock_table,getpid()); 
                  }
                  lfd.f->lock_table = pose_lock(lfd.f->lock_table,newlock);
                  lfd.f->first = premier_element_lock_table (lfd.f->lock_table);
                  //z = lfd_owner_in_lock_owners(*lfd_owner,lfd.f->lock_table[a]);
                }else if (lfd.f->lock_table[a].starting_offset < lck -> l_start && lfd.f->lock_table[a].len > lck ->l_len){ // cas où une partie interne du verrou est effacé, on sépare le verrou en deux verrous
                  printf("suppression d'une partie du lock au milieu,de %ld à %ld\n",lck->l_start,lck->l_len); 
                  rl_lock l1;
                  rl_lock l2;
                  l1.starting_offset = lfd.f->lock_table[a].starting_offset;
                  l1.len = (lck -> l_start) - 1;
                  l1.nb_owners = 1;
                  l1.m = lfd.f->lock_table[a].m;
                  l2.starting_offset = (lck -> l_len) + 1;
                  l2.len = lfd.f->lock_table[a].len;
                  l2.type = lfd.f->lock_table[a].type;
                  l2.nb_owners = 1;
                  l2.m = lock.m;
                  l1.lock_owners[0] = *lfd_owner;
                  l2.lock_owners[0] = *lfd_owner;
                  lfd.f->lock_table = enleve_lock_ou_owner(i[0],i[1],lfd);
                   //if (lfd.f->lock_table[a].nb_owners == 0){
                    a = already_locked(0,lck->l_start,lck->l_len,lfd.f->lock_table,getpid());
                   /* a = already_locked(a,lck->l_start,lck->l_len,lfd.f->lock_table,getpid());
                  }*/
                  lfd.f->lock_table= pose_lock(lfd.f->lock_table,l1);
                  lfd.f->lock_table = pose_lock(lfd.f->lock_table,l2);
                  lfd.f->first = premier_element_lock_table (lfd.f->lock_table);
                  //z = lfd_owner_in_lock_owners(*lfd_owner,lfd.f->lock_table[a]);
                }else{
                  printf("aucune suppression n'est applicable\n"); //On ne devrait jamais avoir ce message
                }
              }else{
                a = already_locked (a+1,lck->l_start,lck->l_len,lfd.f->lock_table,getpid());
              }
          }
        }
      }
      return 0;
    }else if (lck->l_type == F_RDLCK){
      if (lck->l_len == 0){
        lck -> l_start = 0;
        lck -> l_len = buf.st_size;
      }
      int a = already_locked(0,lck->l_start,lck->l_len,lfd.f->lock_table,getpid());
      if (a!=-1){
        /*
        Si on a déjà un verrou qui est en partie ou entiérement a l'endroit où l'on veut mettre le notre : 
        -Si il est de type F_WRLCK et qu'il y a d'autres propriétaires que le processus appellant on renvoie -1
        -On renvoie aussi -1 s'il n'y a qu'un owner mais que ce n'est pas le processus appellant
        -Sinon on le déverrouille*/  
        int z = lfd_owner_in_lock_owners(*lfd_owner,lfd.f->lock_table[a]);
        struct flock lck2;
        lck2.l_type = F_UNLCK;
        lck2.l_whence = SEEK_SET;
        lck2.l_start = lck->l_start;
        lck2.l_len = lck->l_len;
        lck2.l_pid = getpid();
        if (lfd.f->lock_table[a].type == F_WRLCK){
          if (/*lfd.f->lock_table[a].nb_owners > 1 || (lfd.f->lock_table[a].nb_owners == 1 &&*/ z == -1){
            return -1;
          } 
          rl_fcntl(lfd,F_SETLK,&lck2);
        }else{
          if (z != -1){
            if(lfd.f->lock_table[a].len >= lck->l_start && lck->l_len <= lfd.f->lock_table[a].len){
              printf("Vous avez déjà un verrou de lecture sur cet emplacement\n");
              return -1;
            }
            rl_fcntl(lfd,F_SETLK,&lck2);
          }
        }
      }
      //On pose le verrou 
      memory *mem = (memory *) malloc (sizeof(memory));
      int code;
      mem -> libre = false;
      code = initialiser_mutex(&mem->mutex);
      if(code > 0) thread_error(__FILE__, __LINE__, code, "init_mutex");
      code = initialiser_cond(&mem->rcond);
      if(code > 0) thread_error(__FILE__, __LINE__, code, "init_rcond");
      code = initialiser_cond(&mem->wcond);
      if(code > 0) thread_error(__FILE__, __LINE__, code, "init_wcond");
      rl_lock newlock;
      newlock.nb_owners = 1;
      newlock.type = lck->l_type;
      newlock.starting_offset = lck->l_start;
      newlock.len = lck->l_len;
      newlock.lock_owners[0] = *lfd_owner;
      newlock.m = mem;
      lfd.f->lock_table = pose_lock(lfd.f->lock_table,newlock);
      lfd.f->first = premier_element_lock_table (lfd.f->lock_table);
      return 0;
    }else{
      if (lck->l_len == 0){
        lck -> l_start = 0;
        lck -> l_len = buf.st_size;
      }
      int a = already_locked(0,lck->l_start,lck->l_len,lfd.f->lock_table,getpid());
      if (a != -1){
        int z = lfd_owner_in_lock_owners(*lfd_owner,lfd.f->lock_table[a]);
        if (lfd.f->lock_table[a].nb_owners > 1 || (lfd.f->lock_table[a].nb_owners == 1 && z == -1)){
          perror("EAGAIN");
          return -1;
        }
        if(lfd.f->lock_table[a].type == F_WRLCK && lfd.f->lock_table[a].starting_offset >= lck->l_start && lck->l_len <= lfd.f->lock_table[a].len){
          printf("Vous avez déjà un verrou d'écriture  sur cet emplacement\n");
          return -1;
        }
        struct flock lck2;
        lck2.l_type = F_UNLCK;
        lck2.l_whence = SEEK_SET;
        lck2.l_start = lck->l_start;
        lck2.l_len = lck->l_len;
        lck2.l_pid = getpid();
        rl_fcntl(lfd,F_SETLK,&lck2);
      }
      memory *mem = (memory *) malloc (sizeof(memory));
      int code;
      mem -> libre = false;
      code = initialiser_mutex(&mem->mutex);
      if(code > 0) thread_error(__FILE__, __LINE__, code, "init_mutex");
      code = initialiser_cond(&mem->rcond);
      if(code > 0) thread_error(__FILE__, __LINE__, code, "init_rcond");
      code = initialiser_cond(&mem->wcond);
      if(code > 0) thread_error(__FILE__, __LINE__, code, "init_wcond");
      rl_lock newlock;
      newlock.nb_owners = 1;
      newlock.type = lck->l_type;
      newlock.starting_offset = lck->l_start;
      newlock.len = lck->l_len;
      newlock.lock_owners[0] = *lfd_owner;
      newlock.m = mem;
      lfd.f->lock_table = pose_lock(lfd.f->lock_table,newlock);
      lfd.f->first = premier_element_lock_table (lfd.f->lock_table);
      return 0;
    }
  }
  return -1;
}


//6.5
rl_descriptor rl_dup(rl_descriptor lfd) {
    int newd = dup(lfd.d);
    if (newd == -1) {
        perror("dup");
        rl_descriptor new_rl_descriptor = { .d = newd, .f = lfd.f };
        return new_rl_descriptor;
        //exit(1);
    }
    int indice = lfd.f->first;
    if (indice == -2) {
        perror("no locks");
        rl_descriptor new_rl_descriptor = { .d = newd, .f = lfd.f };
        return new_rl_descriptor;
    }
    int val = lfd.d;
    int pid = (int)getpid();
    rl_lock* lock_tableTMP = lfd.f->lock_table;
    while (indice >= 0) {
        int len = lock_tableTMP[indice].nb_owners;
        for (int i = 0; i < len; i++) {
            if ((lock_tableTMP[indice].lock_owners[i]).des == val) {
                if ((int)(lock_tableTMP[indice].lock_owners[i]).proc == pid){
                    //owner new_owner = { .proc = getpid(), .des = newd };
                    lock_tableTMP[indice].lock_owners[lock_tableTMP[indice].nb_owners].proc = pid;
                    lock_tableTMP[indice].lock_owners[lock_tableTMP[indice].nb_owners].des = newd;
                    lock_tableTMP[indice].nb_owners += 1;
                }
            }
        }
        indice = lock_tableTMP[indice].next_lock;
    }
    rl_descriptor new_rl_descriptor = { .d = newd, .f = lfd.f };
    return new_rl_descriptor;
}

rl_descriptor rl_dup2(rl_descriptor lfd, int newd) {
    int r = dup2(lfd.d, newd);
    if (r == -1) {
        perror("dup2");
        rl_descriptor new_rl_descriptor = { .d = newd, .f = lfd.f };
        return new_rl_descriptor;
        //exit(1);
    }
    int indice = lfd.f->first;
    if (indice == -2) {
        perror("no locks");
        rl_descriptor new_rl_descriptor = { .d = newd, .f = lfd.f };
        return new_rl_descriptor;
    }
    int val = lfd.d;
    int pid = (int)getpid();
    rl_lock* lock_tableTMP = lfd.f->lock_table;
    while (indice >= 0) {
        int len = lock_tableTMP[indice].nb_owners;
        for (int i = 0; i < len; i++) {
            if ((lock_tableTMP[indice].lock_owners[i]).des == val) {
                if ((int)(lock_tableTMP[indice].lock_owners[i]).proc == pid) {
                    //owner new_owner = { .proc = getpid(), .des = newd };
                    lock_tableTMP[indice].lock_owners[lock_tableTMP[indice].nb_owners].proc = pid;
                    lock_tableTMP[indice].lock_owners[lock_tableTMP[indice].nb_owners].des = newd;
                    lock_tableTMP[indice].nb_owners += 1;
                }
            }
        }
        indice = lock_tableTMP[indice].next_lock;
    }
    rl_descriptor new_rl_descriptor = { .d = newd, .f = lfd.f };
    return new_rl_descriptor;
}

//6.6
pid_t rl_fork() {
    pid_t pid = fork();
    if ((int)pid == -1) {
        perror("fork");
        return -1;
    }
    if ((int)pid == 0) {
        
        if(rl_all_files.nb_files == 0) {
            return pid;
        }
        rl_open_file * tabFileTmp = (*rl_all_files.tab_open_files);
        
        pid_t parent = getppid();
        int cpid = (int)getpid();
        
        int indice = tabFileTmp->first;
        rl_lock* lock_tableTMP = tabFileTmp->lock_table;
        while (indice >= 0) {
            int len = lock_tableTMP[indice].nb_owners;
            for (int i = 0; i < len; i++) {
                if ((lock_tableTMP[indice].lock_owners[i]).proc == parent) {
                    //owner new_owner = { .proc = getpid(), .des = identique };
                    lock_tableTMP[indice].lock_owners[lock_tableTMP[indice].nb_owners].proc = cpid;
                    lock_tableTMP[indice].lock_owners[lock_tableTMP[indice].nb_owners].des = (lock_tableTMP[indice].lock_owners[i]).des;
                    lock_tableTMP[indice].nb_owners += 1;
                    
                }
            }
            indice = lock_tableTMP[indice].next_lock;
        }
    }
    return pid;
}

//6.8
int rl_init_library() {
  for (int i = 0; i < NB_FILES; i++){
    rl_all_files.tab_open_files[i] = (rl_open_file *) malloc (sizeof (rl_open_file));
  }
  rl_all_files.nb_files = 0;
  return 0;
}

void print_all (){
  printf("rl_all_files.nb_files = %d\n",rl_all_files.nb_files);
  for(int i = 0; i < rl_all_files.nb_files; i++){
    rl_open_file* files = rl_all_files.tab_open_files[i];
    int id = files->first;
    printf("  tab_open_files[%d] first = %d\n", i, id);
    rl_lock * lock = files-> lock_table;
    for(int j = 0; j < NB_LOCKS; j++){
      if(id < 0){
        break;
      }
      printf("    lock_table[%d]:\n", id);
      printf("      nextlock : %d:\n", lock[id].next_lock);
      printf("      starting_offset : %d\n", (int)lock[id].starting_offset);
      printf("      len : %d\n", (int)lock[id].len);
      printf("      type : %d\n", (int)lock[id].type);
      printf("      nb_owners : %d\n", (int)lock[id].nb_owners);
      for(int k = 0; k <(int)lock[id].nb_owners; k++ ){
        owner o = lock[id].lock_owners[k];
        printf("      owners [%d]: \n", k);
        printf("        proc : %d\n", (int)o.proc);
        printf("        des : %d\n", (int)o.des);
      }
      //printf memory
      id = lock[id].next_lock;
    }
  }
}
