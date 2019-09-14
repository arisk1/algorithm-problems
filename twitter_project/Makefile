OBJS1 = functions.o classes.o hashT.o initialization.o recommendation.o assignments.o update.o combinations.o silhoutte.o prerec.o recommend.o
SOURCE = recommendation.cpp prerec.cpp hashT.cpp functions.cpp classes.cpp initialization.cpp assignments.cpp update.cpp combinations.cpp silhoutte.cpp recommend.cpp
HEADER = classes.h functions.h hashT.h initialization.h assignments.h update.h combinations.h silhoutte.h prerec.h recommend.h
OUT1 = recommendation
CC = g++
FLAGS = -g -c -std=c++11

all: $(OUT1) 

$(OUT1): $(OBJS1)
	$(CC) -g $(OBJS1) -o $@
classes.o: classes.cpp
	$(CC) $(FLAGS) classes.cpp
functions.o: functions.cpp
	$(CC) $(FLAGS) functions.cpp
initialization.o :initialization.cpp
	$(CC) $(FLAGS) initialization.cpp
assignments.o: assignments.cpp
	$(CC) $(FLAGS) assignments.cpp
update.o: update.cpp
	$(CC) $(FLAGS) update.cpp
hashT.o: hashT.cpp
	$(CC) $(FLAGS) hashT.cpp
combinations.o: combinations.cpp
	$(CC) $(FLAGS) combinations.cpp
silhoutte.o: silhoutte.cpp
	$(CC) $(FLAGS) silhoutte.cpp
prerec.o: prerec.cpp
	$(CC) $(FLAGS) prerec.cpp
recommendation.o: recommendation.cpp
	$(CC) $(FLAGS) recommendation.cpp  
recommend.o: recommend.cpp
	$(CC) $(FLAGS) recommend.cpp 
clean :
	rm -f  $(OBJS1) $(OUT1) 

count :
	wc $(SOURCE) $(HEADER)
