int gradesort( int fd);

struct evaluation{
  char  id[16];
  char  surname1[32];
  char  surname2[32];
  char  name[32];
  float grade1;
  float grade2;
  float avgrade;
  char  photofilename[20];
  int   photosize;
  char  photodata[16000];
};
