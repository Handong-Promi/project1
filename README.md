This Project is for <2020-1 Open Sourse Software Lab, Handong Global University>
================================================================================

_Author : Lee Wonbin_
_Program : Managing movies in theater_


## The program consists of __three files.__

1. __movie_main.c__
	- Managing all of the menus. 

2. __movie.c__
	- Library functions.

3. __movie.h__
	- Structures, Macro, Function prototypes.

******

## Details 

1. __movie_main.c__   

   i) __menu__

   - Create   
	 Create a new movie record, and the information of that record is given from the user.
	
	-  Read   
	   Read a movie record searched by a certain title.   
	   Or, read movie records searched by genre or distributor or minimum viewing age or state.

	- Update   
	  Update a movie record searched by a certain title.

	- Update by cases   
	  Update some movie records by genre or distributor or minimum viewing age or state.

	- Delete   
	  Delete a movie record searched by a certain title.

	- Delete by cases   
	  Delete some movie records by genre or distributor or minimum viewing age or state.

	- List   
	  Print all of the movie records.

	- Tidy up   
	    : Araange the movie records so that there is no null pointer between valid movie records.

	- Sort   
	  Sort the movie records by title or genre or distributor or minimum viewing age or state. The standard is ASKII CODE.

	- Print statistics   
	  Print statistics about movie records on the screen.

	- Save statistics   
	  Save statistics about movie records to a certain data file.

	- Load   
	  Load movie records from a certain data file.

	- Save   
	  Save movie records to a certain data file.

	- Report   
	  Save movie records and their statistics to a certain data file, keeping a given form.

   ii) __Characteristic__   
    - All of the movie_main.c's functions don't directly access to movie records. This means, this file is an application file. 


2. __movie.c__   
	
   i) __contents__   
   - It contains movie record pointer array.   
   - It contains some limited info about movies. EX) genres, ages, states.
   - It contains functions that used movie_main.c.   

   ii) __Characteristic__
   - There is no limit for directly accesing to movie record. Therefore, all of functions in this file can do so.

   iii) __Kinds of Info__
   	- _TITLE_ : naming by you or data file.   
	- _GENRE_ : Action, Melo, Thriller, Comedy, Mystery, Adventure, SF, Fantasy, Drama // __Be careful at CAPITAL__ 
	- _DISTRIBUTOR_ : naing by you or data file.
	- _MINIMUM VIEWING AGE_ : ALL, 7, 12, 15, 18
	- _STATE_ : due for release, on screen   


3. __movie.h__
 
   - It just contains a structure type for movie record, and function decleraitons(prototypes) for both of movie_main.c and movie.c

******

## ETC)
  
  1. __Makefile__   
     : You can simply make a executable file via using make utility

	   - make movie : movie executable file is made.
	   - make movie_debug : movie executable file applied DEBUG is made. This file is for debugging.
       - make clean : remove all of the object files.
	   - make cleanx : remove all of the object files and executable file(movie)

  2. __data.txt__   
     : This file includes 50 movie information. And, this file exists for teting load menu.



