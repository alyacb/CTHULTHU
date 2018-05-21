CXX = g++
CXXFLAGS = -std=c++14 -Werror=vla -I../include -I/matrix/ -I/tst/ -I/shared/ -Wall -MMD
OBJECTS = main.o tst/test_var.o shared/err.o matrix/matrix_ops.o matrix/matrix_api.o tst/test_matrix.o matrix/matrix_mult.o shared/util.o tst/test.o matrix/matrix_class.o matrix/matrix_eigen.o 
DEPENDS = ${OBJECTS:.o=.d}
EXEC = CTHULTHU

default: ${EXEC}

debug: CXXFLAGS += -DDEBUG -g
debug: ${EXEC}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm *.o *.d tst/*.o tst/*.d matrix/*.o matrix/*.d shared/*.o shared/*.d ${EXEC}
