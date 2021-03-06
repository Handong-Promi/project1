#include "movie.h"
#include <stdlib.h>

T_Movie* movies[MAX_MOVIES];
int _count = 0;

char genre_list[9][20] = {"Action", "Melo", "Thriller", "Comedy", "Mystery", "Adventure", "SF", "Fantasy", "Drama"};
const int genre_size = sizeof(genre_list) / sizeof(genre_list[0]);

int age_list[5] = {1, 7, 12, 15, 18};
char str_age_list[5][10] = {"ALL", "7", "12", "15", "18"};
const int age_size = sizeof(age_list) / sizeof(age_list[0]);

char state_real[2][20] = {"Due for Release", "On Screen"};
int state[2] = {0, 1};
const int state_size = sizeof(state)/sizeof(state[0]);

int mv_is_available(){
    int i;
    for(i=0;i<MAX_MOVIES;i++){
	if(movies[i] == NULL) return 1;
    }
    return 0;
}

int mv_first_available(){
    int i;
    for(i=0;i<MAX_MOVIES;i++){
		if(movies[i] == NULL){
#ifdef DEBUG
			printf("[DEBUG] First available index is %d\n", i);
#endif
			return i;
   	 	}
	}
  	return -1;
}

void mv_init(){
    int i;
    for(i=0;i<MAX_MOVIES;i++){
		if(movies[i]!=NULL){
#ifdef DEBUG
			printf("[DEBUG] Now, delete the movie : %s\n", movies[i]->title);
#endif
	 	    free(movies[i]);			
		    movies[i]=NULL; // to prevent dangling pointer problem.
		}
    }
    _count = 0;
} 

int mv_count(){
    return _count;
}

//Below fuctions are used in (1)create menu. (First using place)

T_Movie* mv_search_by_title(char *t){
    int i;
    for(i=0; i<MAX_MOVIES;i++){
	if(movies[i]!=NULL && strcmp(movies[i]->title, t)==0){
	    return movies[i];
        }
    }
    return NULL;
}

int mv_valid_about_genre(char *g){
    int i;
    for(i=0;i<genre_size;i++){
		if(strcmp(genre_list[i], g)==0) return 1;
    }
    return 0;
}
 
int mv_valid_about_age(int a){
    int i;
    for(i=0;i<age_size;i++){
		if(a == age_list[i]) return 1;
    }
    return 0;
}

int mv_valid_about_age_file(char* a){
    int i;
    for(i=0;i<age_size;i++){
		if(strcmp(str_age_list[i], a)==0) return 1;
    }
    return 0;
}

int mv_valid_about_state(int s){
    int i;
    for(i=0;i<state_size;i++){
	if(s == state[i]) return 1;
    }
    return 0;
}

int mv_valid_about_state_file(char* s){
    int i;
    for(i=0;i<state_size;i++){
		if(strcmp(state_real[i], s)==0) return 1;
    }
    return 0;
}

void mv_create(char *t, char *g, char *d, int a, int s){
    int index = mv_first_available();
    char str[10]; 
    movies[index] = (T_Movie*)malloc(sizeof(T_Movie));
    T_Movie* p = movies[index];
    strcpy(p->title, t);
    strcpy(p->genre, g);
    strcpy(p->distri, d);
    if(a!=1){
        sprintf(str, "%d", a);
        strcpy(p->age, str);
    }
    else{
	strcpy(str, "ALL");
	strcpy(p->age, str);
    }
    strcpy(p->state,state_real[s]);
    _count++;
}

void mv_create_by_file(char *t, char *g, char *d, char *a, char *s){
    int index = mv_first_available();
    movies[index] = (T_Movie*)malloc(sizeof(T_Movie));
    T_Movie* p = movies[index];
    strcpy(p->title, t);
    strcpy(p->genre, g);
    strcpy(p->distri, d);
	strcpy(p->age, a);
    strcpy(p->state,s);
    _count++;
}

//Bellow functions are used in (2)read menu. + list menu

char* mv_get_title(T_Movie* p){
    return p->title;
}
char* mv_get_genre(T_Movie* p){
    return p->genre;
}
char* mv_get_distri(T_Movie* p){
    return p->distri;
}

char* mv_get_age(T_Movie* p){
    return p->age;
}

char* mv_get_state(T_Movie* p){
    return p->state;
}

// Below functions are used in menus related to update.

void mv_update(T_Movie* p, char* g, char* d, int a, int s){
	
    char str[10]; 

    strcpy(p->genre, g);
    strcpy(p->distri, d);
    if(a!=1){
        sprintf(str, "%d", a);
        strcpy(p->age, str);
    }
    else{
	strcpy(str, "ALL");
	strcpy(p->age, str);
    }
    strcpy(p->state,state_real[s]);
#ifdef DEBUG
	printf("Movie [%s] is updated!\n", p->title);
#endif
}

void mv_update_by_genre(T_Movie* p, char* g){
	strcpy(p->genre, g);
}
void mv_update_by_distri(T_Movie* p, char* d){
	strcpy(p->distri, d);
}
void mv_update_by_age(T_Movie* p, int a){
	
    char str[10]; 

    if(a!=1){
        sprintf(str, "%d", a);
        strcpy(p->age, str);
    }
    else{
	strcpy(str, "ALL");
	strcpy(p->age, str);
    }
}
void mv_update_by_state(T_Movie* p, int s){
	strcpy(p->state, state_real[s]);
}
char* get_state(int s){
	return state_real[s];
}

// Below functions are used in menus related to delete.
void mv_delete(T_Movie* p){
#ifdef DEBUG
	char title[50];
	strcpy(title, p->title);
#endif
	int index;
	for(int i=0; i<MAX_MOVIES; i++){
		if(movies[i]==p){
			index = i;
			break;
		}
	}
	free(p);
	movies[index] = NULL;
	_count--;
#ifdef DEBUG
	printf("Movie [%s] is deleted!\n", title);
#endif
}

// for saving files

int mv_get_titles_save(char* mt[]){

    int i, c=0;
    for(i=0;i<MAX_MOVIES;i++){
		if(movies[i]!=NULL){
			mt[c] = movies[i]->title;
	   	 c++;
		}
    }
    return c;
}

int mv_get_distris_save(char* md[]){

    int i, c=0;
    for(i=0;i<MAX_MOVIES;i++){
		int dub = 0;
		if(movies[i]!=NULL){
			for(int j=0; j<c;j++){
				if(strcmp(md[j], movies[i]->distri)==0){
					dub = 1;
					break;
				}
			}
			if(dub==0){
				md[c] = movies[i]->distri;
				c++;
			}
		}
    }
    return c;
}
// end

void mv_get_all(T_Movie* a[]){
	int i, c=0;
	for(i=0;i<MAX_MOVIES; i++){
		if(movies[i] != NULL){
			a[c]=movies[i];
			c++;
		}
	}
}

int mv_get_some_by_genre(T_Movie* a[], char* g){
    int i, c=0;
    for(i=0;i<MAX_MOVIES;i++){
	if(movies[i]!=NULL&&strcmp(movies[i]->genre, g)==0){
	    a[c] = movies[i];
	    c++;
	}
    }
    return c;
}

int mv_get_some_by_distri(T_Movie* a[], char* d){
    int i, c=0;
    for(i=0;i<MAX_MOVIES;i++){
	if(movies[i]!=NULL&&strcmp(movies[i]->distri, d)==0){
	    a[c] = movies[i];
	    c++;
	}
    }
    return c;
}

int mv_get_some_by_age(T_Movie* a[], int age){
    int i, c=0;
    char str[10];
 
    if(age!=1){
        sprintf(str, "%d", age);
    }
    else{
	strcpy(str, "ALL");
    }

    for(i=0;i<MAX_MOVIES;i++){
	if(movies[i]!=NULL&&strcmp(movies[i]->age, str)==0){
	    a[c] = movies[i];
	    c++;
	}
    }
    return c;
}

int mv_get_some_by_state(T_Movie* a[], int s){
    int i, c=0;
    for(i=0;i<MAX_MOVIES;i++){
	if(movies[i]!=NULL&&strcmp(movies[i]->state, state_real[s])==0){
	    a[c] = movies[i];
	    c++;
	}
    }
    return c;
}

char* mv_to_string(T_Movie* p){
    static char str[150];
    
    char t[50];
    strcpy(t, p->title);
    strcat(t, "]");
    char g[50];
    strcpy(g, p->genre);
    strcat(g, "]");
    char d[50];
    strcpy(d, p->distri);
    strcat(d, "]");
    char a[50];
    strcpy(a, p->age);
    strcat(a, "]");
    char s[50];
    strcpy(s, p->state);
    strcat(s, "]");

    sprintf(str, "[%-40s\t / [%-15s\t / [%-20s\t / [%-5s\t / [%s", t, g, d, a, s);
    return str;
}

//Below functions are used in tidy_up and sort menus....
void arrange_order(){

#ifdef DEBUG
	printf("-------------------------------------\n");
	printf("[DEBUG] Before arranging...\n");
	for(int i=0;i<MAX_MOVIES;i++){
		if(movies[i]==NULL){
			printf("[DEBUG] movies[%d]: NULL\n", i);
		}
		else printf("{DEBUG] movies[%d]: %s\n", i, movies[i]->title);
	}
	printf("-------------------------------------\n");
#endif

	for(int i=0; i<MAX_MOVIES-1; i++){
		int count_limit = MAX_MOVIES-1 - i; // this means, how many times the while loop can execute.
		int count = 0; // for check : already tidy up MAX_MOVIES-1-i), but it is still NULL. That means, all of after movies[i] are NULL.
		int flag = 0; // to check whether count is MAX_MOVIES-1-i or not.
		
		while(movies[i]==NULL){
			for(int j=i; j<MAX_MOVIES-1;j++){
				movies[j] = movies[j+1];
				movies[j+1] = NULL;
			}
			count++;
#ifdef DEBUG
			printf("[DEBUG] movie reoord index :            %d\n", i);
			printf("[DEBUG] total arraging count :          %d\n", count);
			printf("[DEBUG] count_limit;(MAX_MOVIES-1)-i) : %d\n\n", count_limit);
#endif
			if(count==count_limit&&movies[i]==NULL){
				flag=1;
				break;
			}	
		}
		if(flag==1) break;
#ifdef DEBUG
		printf("Index [%d] is now filled up! : %s\n\n", i, movies[i]->title);
#endif
	}	
#ifdef DEBUG
	printf("-------------------------------------\n");
	printf("[DEBUG] After arranging...\n");
	for(int i=0;i<MAX_MOVIES;i++){
		if(movies[i]==NULL){
			printf("[DEBUG] movies[%d]: NULL\n", i);
		}
		else printf("{DEBUG] movies[%d]: %s\n", i, movies[i]->title);
	}
	printf("-------------------------------------\n");
#endif
}	

void sort(int option){
	
	arrange_order();

	switch(option){
		case 1:
			for(int i=0; i<_count-1; i++){
				for(int j=0; j<_count-1; j++){
					if(strcmp(movies[j]->title,movies[j+1]->title)>0){
#ifdef DEBUG
						printf("[%s] vs [%s]\n", movies[j]->title, movies[j+1]->title);
#endif
						T_Movie* temp;
						temp = movies[j];
						movies[j] = movies[j+1];
						movies[j+1] = temp;
					}
				}
			}
			break;
		case 2:
			for(int i=0; i<_count-1; i++){
				for(int j=0; j<_count-1; j++){
					if(strcmp(movies[j]->genre,movies[j+1]->genre)>0){
#ifdef DEBUG
						printf("[%s] vs [%s]\n", movies[j]->genre, movies[j+1]->genre);
#endif
						T_Movie* temp;
						temp = movies[j];
						movies[j] = movies[j+1];
						movies[j+1] = temp;
					}
				}
			}
			break;
		case 3:
			for(int i=0; i<_count-1; i++){
				for(int j=0; j<_count-1; j++){
					if(strcmp(movies[j]->distri,movies[j+1]->distri)>0){
#ifdef DEBUG
						printf("[%s] vs [%s]\n", movies[j]->distri, movies[j+1]->distri);
#endif
						T_Movie* temp;
						temp = movies[j];
						movies[j] = movies[j+1];
						movies[j+1] = temp;
					}
				}
			}
			break;
		case 4:
			for(int i=0; i<_count-1; i++){
				for(int j=0; j<_count-1; j++){
				    int a = atoi(movies[j]->age); // if atoi cannot convert anything, return 0
					int b = atoi(movies[j+1]->age);
					if(a==0) a++;
					if(b==0) b++;
					if(a>b){
#ifdef DEBUG
						printf("[%s] vs [%s]\n", movies[j]->age, movies[j+1]->age);
#endif
						T_Movie* temp;
						temp = movies[j];
						movies[j] = movies[j+1];
						movies[j+1] = temp;
					}
				}
			}
			break;
		case 5:
			for(int i=0; i<_count-1; i++){
				for(int j=0; j<_count-1; j++){
					if(strcmp(movies[j]->state,movies[j+1]->state)>0){
#ifdef DEBUG
						printf("[%s] vs [%s]\n", movies[j]->state, movies[j+1]->state);
#endif
						T_Movie* temp;
						temp = movies[j];
						movies[j] = movies[j+1];
						movies[j+1] = temp;
					}
				}
			}
			break;
		default:
			break;
	}
}

//Bellow functions are used in menus related to statistics or file

void print_statistics(int g[], int a[], int s[]){
	
	printf("Getting Statistics...\n");

	printf("\n-----[GENRE]-----\n");
	for(int i=0;i<genre_size;i++){
		printf("%d. [%s] : %d\n", i+1, genre_list[i], g[i]);
	}

	printf("\n-----[MINIMUN VIEWING AGE]-----\n");
	for(int i=0;i<age_size;i++){
		printf("%d. [%s] : %d\n", i+1, str_age_list[i], a[i]);
	}

	printf("\n-----[STATE]-----\n");
	for(int i=0;i<state_size;i++){
		printf("%d. [%s] : %d\n", i+1, state_real[i], s[i]);
	}
}

void save_statistics(char* filename, int g[], int a[], int s[]){
	
	
	FILE* f = fopen(filename, "w");

	fprintf(f, "-----[GENRE]-----\n");
	for(int i=0;i<genre_size;i++){
		fprintf(f, "%d. [%s] : %d\n", i+1, genre_list[i], g[i]);
	}

	fprintf(f, "-----[Minimun Viewing Age]-----\n");
	for(int i=0;i<age_size;i++){
		fprintf(f, "%d. [%s] : %d\n", i+1, str_age_list[i], a[i]);
	}

	fprintf(f, "-----[State]-----\n");
	for(int i=0;i<state_size;i++){
		fprintf(f, "%d. [%s] : %d\n", i+1, state_real[i], s[i]);
	}
	printf("\nMovie statistics is now stored in %s!\n", filename);
	fclose(f);
}

void mv_count_genre(int g[]){
	
	for(int i=0;i<genre_size;i++){
		g[i] = 0;
	}

	for(int i=0;i<MAX_MOVIES;i++){
		if(movies[i]==NULL) continue;
		for(int j=0;j<genre_size;j++){
			if(!strcmp(movies[i]->genre,genre_list[j])){
#ifdef DEBUG
			printf("[DEBUG] [%s]'s genre is [%s]\n",movies[i]->title, movies[i]->genre);
#endif
			g[j]++;
			break;
			}
		}
	}
#ifdef DEBUG
	printf("\n");
#endif
	return;
}

void mv_count_age(int a[]){

	for(int i=0;i<age_size;i++){
		a[i] = 0;
	}

	for(int i=0;i<MAX_MOVIES;i++){
		if(movies[i]==NULL) continue;
		for(int j=0;j<age_size;j++){
			if(!strcmp(movies[i]->age,str_age_list[j])){
#ifdef DEBUG
			printf("[DEBUG] [%s]'s minimum viewing age is [%s]\n", movies[i]->title,movies[i]->age);
#endif
			a[j]++;
			}
		}
	}
#ifdef DEBUG
	printf("\n");
#endif
	return;
}

void mv_count_state(int s[]){
	
	for(int i=0;i<state_size;i++){
		s[i] = 0;
	}

	for(int i=0;i<MAX_MOVIES;i++){
		if(movies[i]==NULL) continue;
		for(int j=0;j<state_size;j++){
			if(!strcmp(movies[i]->state,state_real[j])){
#ifdef DEBUG
			printf("[DEBUG] [%s]'s state is [%s]\n",movies[i]->title,movies[i]->state);
#endif
			s[j]++;
			}
		}
	}
#ifdef DEBUG
	printf("\n");
#endif
	return;
}

const int get_genre_size(){
	return genre_size;
}
const int get_age_size(){
	return age_size;
}
const int get_state_size(){
	return state_size;
}

// Below functions are used in file menus

char* mv_to_string_save(T_Movie* p){
	
    static char str[150];
    
    sprintf(str, "%s\n%s %s\n%s %s", p->title, p->genre, p->distri, p->age, p->state);
    return str;
}

void report_about_titles(FILE* f){
	
#ifdef DEBUG
	printf("report saving start...\n");
#endif

	fprintf(f, "<1> Registered movies\n-\n");
	
	char* mv_t[MAX_MOVIES];
	int size = mv_get_titles_save(mv_t);

	for(int i=0;i<size;i++){
		char order[10]; sprintf(order, "%d.", i+1); 
		fprintf(f, "%-3s %s\n", order, mv_t[i]);
	}
	fprintf(f, "\n\n");

#ifdef DEBUG
	printf("[DEBUG] Done of saving movie titles! keep saving...\n\n");
#endif
}

void report_about_states(FILE* f){
	
	fprintf(f, "<2> Movies by state\n-\n");	

	for(int i=0;i<state_size;i++){
		T_Movie* movies_by_state[MAX_MOVIES];
		int size = mv_get_some_by_state(movies_by_state, state[i]);
		fprintf(f,"[%d] %s : %d movies\n", i+1, state_real[i], size);
		for(int j=0;j<size;j++){
			char order[10]; sprintf(order, "%d.",j+1); 
			fprintf(f, "%-3s %s\n", order, mv_get_title(movies_by_state[j]));
		}
		fprintf(f, "\n\n");
#ifdef DEBUG
	printf("[DEBUG] movies of %s  are saved! keep saving...\n", state_real[i]);
#endif
	}

#ifdef DEBUG
	printf("[DEBUG] Done of saving movies by state! keep saving...\n\n");
#endif
}	
		
void report_about_genres(FILE* f){
	
	fprintf(f, "<3> movies by genres\n-\n");

	for(int i =0; i<genre_size;i++){
		T_Movie* movies_by_genre[MAX_MOVIES];
		int size = mv_get_some_by_genre(movies_by_genre, genre_list[i]);
		fprintf(f, "[%d] %s : %d movies\n", i+1, genre_list[i], size);
		for(int j=0; j<size; j++){
			char order[10]; sprintf(order, "%d.",j+1); 
			fprintf(f, "%-3s %s\n", order, mv_get_title(movies_by_genre[j]));
		}
		fprintf(f, "\n\n");
#ifdef DEBUG
		printf("[DEBUG] movies of %s are saved! keep saving...\n", genre_list[i]);
#endif
	}
			
#ifdef DEBUG
	printf("[DEBUG] Done of saving movies by genre! keep saving...\n\n");
#endif
}

void report_about_ages(FILE* f){
	
	fprintf(f, "<4> movies by minimum viewing ages\n-\n");

	for(int i =0; i<age_size;i++){
		T_Movie* movies_by_age[MAX_MOVIES];
		int size = mv_get_some_by_age(movies_by_age, age_list[i]);
		fprintf(f, "[%d] %s : %d movies\n", i+1, str_age_list[i], size);
		for(int j=0; j<size; j++){
			char order[10]; sprintf(order, "%d.",j+1); 
			fprintf(f, "%-3s %s\n", order, mv_get_title(movies_by_age[j]));
		}
		fprintf(f, "\n\n");
#ifdef DEBUG
		printf("[DEBUG] movies of %s are saved! keep saving...\n", str_age_list[i]);
#endif
	}
			
#ifdef DEBUG
	printf("[DEBUG] Done of saving movies by age! keep saving...\n\n");
#endif
}

void report_about_distris(FILE* f){
	
	fprintf(f, "<5> list of distributors\n-\n");
	
	char* distri[MAX_MOVIES];
	int size = mv_get_distris_save(distri);

	fprintf(f, "[Total] : %d kinds of distributors.\n-\n", size);
	for(int i=0; i<size; i++){
		char order[10]; sprintf(order, "%d.",i+1); 
		fprintf(f, "%-3s %s\n", order, distri[i]);
	}

#ifdef DEBUG
	printf("[DEBUG] Done of saving distributors of movies! end saving...\n\n");
#endif
}
