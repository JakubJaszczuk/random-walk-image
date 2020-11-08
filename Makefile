CXX = g++
CXXFLAGS = -Wall -Wextra -O3 -ftree-vectorize -march=native -flto -std=c++20
LDFLAGS = -lfmt
TARGET = RandomWalker
ARGS = 
OBJDIR = obj
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:%.cpp=$(OBJDIR)/%.o)
DBJS = $(SRCS:%.cpp=$(OBJDIR)/%.d)

.PHONY: all
all: $(TARGET)

$(OBJDIR)/%.d: %.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -MM $< > $@

$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $@

-include $(DBJS)

.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJS) $(DBJS)

.PHONY: run
run:
	./$(TARGET) $(ARGS)
