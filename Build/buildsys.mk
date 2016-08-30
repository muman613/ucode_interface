################################################################################
#	MODULE		:	buildsys.mk
#	DESCRIPTION	:	Advanced build scripts
#	AUTHOR 		:	Michael A. Uman
#	DATE		:	March 15, 2016
################################################################################

ifdef CROSS
	CXX:="$(CROSS)-$(CXX)"
endif

MAKEFILE?=Makefile

VPATH := $(dir $(CPP_SOURCES)) $(dir $(CSOURCES))

CPP_OBJS = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(notdir $(CPP_SOURCES)))
C_OBJS   = $(patsubst %.c, $(OBJ_DIR)/%.o, $(notdir $(C_SOURCES)))

OBJS=$(CPP_OBJS) $(C_OBJS)

ifdef DEBUG
ifeq ($(TARGET_TYPE), dynlib)
	BUILDTYPE?=SharedDebug
else
	BUILDTYPE?=Debug
endif
	CFLAGS+= -D_DEBUG=1 -g3 -Wall
else
ifeq ($(TARGET_TYPE), dynlib)
	BUILDTYPE?=SharedRelease
else
	BUILDTYPE?=Release
endif
	CFLAGS+= -DNDEBUG -O2
endif

#	Specify EXE/OBJ/LIB/DEP paths if not specified by master makefile
ifndef ARCH
EXE_DIR?=bin/$(BUILDTYPE)
OBJ_DIR?=obj/$(BUILDTYPE)
LIB_DIR?=lib/$(BUILDTYPE)
DEP_DIR?=deps/$(BUILDTYPE)
else
EXE_DIR?=bin/$(BUILDTYPE)/$(ARCH)
OBJ_DIR?=obj/$(BUILDTYPE)/$(ARCH)
LIB_DIR?=lib/$(BUILDTYPE)/$(ARCH)
DEP_DIR?=deps/$(BUILDTYPE)/$(ARCH)
endif

ifeq ($(ARCH), x86)
CFLAGS+=-m32
LDFLAGS+=-m32
else
CFLAGS+=-m64
LDFLAGS+=-m64
endif

#	Generate dependancies from source files.
ifeq ($(MAKECMDGOALS),clean)
# doing clean, so dont make deps.
DEPS=
else
CPP_SOURCES_TRIM=$(notdir $(CPP_SOURCES))
DEPS=$(CPP_SOURCES_TRIM:%.cpp=$(DEP_DIR)/%.d)
C_SOURCES_TRIM=$(notdir $(C_SOURCES))
DEPS+=$(notdir $(C_SOURCES_TRIM:%.c=$(DEP_DIR)/%.d))
endif

################################################################################
#	Generate the targets full name
################################################################################
ifeq ($(TARGET_TYPE), exe)
TARGET=$(EXE_DIR)/$(TARGET_EXE)
endif
ifeq ($(TARGET_TYPE), statlib)
TARGET=$(LIB_DIR)/$(LIBNAME).a
endif
ifeq ($(TARGET_TYPE), dynlib)
TARGET=$(LIB_DIR)/$(LIBNAME).so
CFLAGS+=-fPIC
endif

CFLAGS+=$(INCLUDES)
LDFLAGS+=$(EXTERN_LIBS) $(LIBS)


#	Default rules
$(OBJ_DIR)/%.o : %.cpp $(MAKEFILE) | objdir
	@echo "Compiling $*.cpp"
	@$(CXX) 2>&1 -c -o $@ $(CFLAGS) $<

$(OBJ_DIR)/%.o : %.c $(MAKEFILE) | objdir
	@echo "Compiling $*.c"
	@$(CC) 2>&1 -c -o $@ $(CFLAGS) $<
	
################################################################################
#	executable target
################################################################################
ifeq ($(TARGET_TYPE), exe)
$(TARGET): objdir exedir $(OBJS) $(EXTERN_LIBS)
	@echo "Linking $(TARGET)"
	@$(CXX) 2>&1 -o $(TARGET) $(OBJS) $(LDFLAGS)
endif

################################################################################
#	static library target
################################################################################
ifeq ($(TARGET_TYPE), statlib)
$(TARGET): objdir libdir $(OBJS)
	@echo "Generating static library $(TARGET)"
	@$(AR) 2>&1 -r -s $(TARGET) $(OBJS)
endif

################################################################################
#	dynamic library target
################################################################################
ifeq ($(TARGET_TYPE), dynlib)
$(TARGET): objdir libdir $(OBJS)
	@echo "Generating shared library $(TARGET)"
	@$(CXX) 2>&1 -shared $(OBJS) -o $(TARGET) -s $(LDFLAGS)
endif

################################################################################
#	dependancy generation
################################################################################
$(DEP_DIR)/%.d:%.c
	@install -d $(DEP_DIR)
	@echo "Generating dependencies for $*...."
	@echo -n "$(DEP_DIR)/$*.d $(OBJ_DIR)/" > $(DEP_DIR)/$*.d
	@$(CXX) -MM $(CFLAGS) $< >> $(DEP_DIR)/$*.d

$(DEP_DIR)/%.d:%.cpp
	@install -d $(DEP_DIR)
	@echo "Generating dependencies for $<...."
	@echo -n "$(DEP_DIR)/$*.d $(OBJ_DIR)/" > $(DEP_DIR)/$*.d
	@$(CXX) -MM $(CFLAGS) $< >> $(DEP_DIR)/$*.d

clean:
	@echo "Removing all objects, binaries, and dependancies..."
	@rm -rf $(OBJS) $(TARGET) $(DEP_DIR) $(ADD_CLEAN_FILES)

	
objdir: .PHONY
	@echo "Creating object directory..."
	@mkdir -p $(OBJ_DIR) 

exedir: .PHONY
	@echo "Creating exe directory..."
	@mkdir -p $(EXE_DIR)

libdir: .PHONY
	@echo "Creating lib directory..."
	@mkdir -p $(LIB_DIR)

.PHONY:
	@true

