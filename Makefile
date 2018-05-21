CXX = g++
CXXFLAGS = -std=c++14 -Werror=vla -Wall -MMD
OBJECTS = main.o test_var.o err.o matrix_ops.o matrix_api.o test_matrix.o matrix_mult.o util.o test.o matrix_class.o matrix_eigen.o 
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
	rm *.o *.d ${EXEC}
