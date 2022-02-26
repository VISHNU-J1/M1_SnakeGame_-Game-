PROJ_NAME = snakegame
SRC = src/snake_main.c


TEST_SRC =test/test.c\
unity/unity.c
 

ifdef OS
   RM = del /q
   FixPath = $(subst /,\,$1)
   EXEC = exe
else
   ifeq ($(shell uname), Linux)
      RM = rm -rf
      FixPath = $1
	  EXEC = out
   endif
endif

build:
	gcc $(SRC) -Iinc -o $(call FixPath,$(PROJ_NAME).$(EXEC)) -lm
	mkdir build
$(BUILD_DIR):
	mkdir $(BUILD_DIR)

run: build
	./$(call FixPath,$(PROJ_NAME).$(EXEC))

static_analysis:
	cppcheck --enable=all $(SRC)

# clean:
# 	$(RM) $(call FixPath,$(PROJ_NAME).$(EXEC))
# 	$(RM) $(call FixPath,$(BUILD_DIR)/*)
# 	make clean -C doc
# 	rmdir build doc/html
test: $(SRC) $(TEST_SRC)
	gcc $^ $(INC) -o $(call FixPath,$(BUILD_DIR)/$(TEST_PROJ_NAME).$(EXEC))
	./$(BUILD_DIR)/$(TEST_PROJ_NAME).$(EXEC)



coverage:${PROJECT_NAME}
	gcc -fprofile-arcs -ftest-coverage $(SRC) $(INC) -o $(call FixPath,$(BUILD_DIR)/$(TEST_PROJ_NAME).$(EXEC))
	$(call FixPath,$(BUILD_DIR)/$(TEST_PROJ_NAME).$(EXEC))
	gcov -a $(SRC)



doc:
	make -C doc
# build1:
# 	mkdir build1

clean:
	$(RM) $(call FixPath,$(PROJ_NAME).$(EXEC))
	$(RM) $(call FixPath,$(BUILD_DIR)/*)
	make clean -C doc
	rmdir build doc/html




