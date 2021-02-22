# Makefile to compile hexGame, created in C++
# Some ideas from https://makefiletutorial.com/
# Carlos Granados 02.2021

# Some variables
CXX = icc
CXXFLAGS = -O2
LDFLAGS = -g
CPPFLAGS = -g -MMD -MP -MF
RM = rm -rf

TARGET = hexGame

# Some directories
SRC_DIR := ./src
BUILD_DIR := ./build

# All files
# Source files
CPP_SRCS += \
$(SRC_DIR)/graph.cpp \
$(SRC_DIR)/hexGame.cpp \
$(SRC_DIR)/hexGraph.cpp \
$(SRC_DIR)/player.cpp

# Object files
OBJS += \
$(BUILD_DIR)/graph.o \
$(BUILD_DIR)/hexGame.o \
$(BUILD_DIR)/hexGraph.o \
$(BUILD_DIR)/player.o

# Dependency files
CPP_DEPS += \
$(BUILD_DIR)/graph.d \
$(BUILD_DIR)/hexGame.d \
$(BUILD_DIR)/hexGraph.d \
$(BUILD_DIR)/player.d

# Other variables
USER_OBJS :=
LIBS := 



# Build steps
 
# All Target
all: build_dir hexGame

# Create build directory
build_dir:
	@echo 'Creating building directory'
	mkdir -p $(BUILD_DIR)
	@echo ' '

# Tool invocations
hexGame: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Intel C++ Linker'
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Each subdirectory must supply rules for building sources it contributes
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Intel C++ Compiler'
	$(CXX) $(CPPFLAGS)"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

# Clean. Delete $BUILD_DIR
.PHONY: clean
clean:
	$(RM) $(BUILD_DIR)

