#include <fmt/core.h>
#include <random>
#include <fstream>
#include "Vector2d.h"

struct RandomWalker {
	std::mt19937 rng{std::random_device()()};
	std::uniform_int_distribution<int> choice{0, 3};
	Vector2d<uint32_t> data;
	uint32_t lifetime = 100;

	RandomWalker(uint32_t size = 512) : data(size), lifetime(size) {}
	RandomWalker(uint32_t size, uint32_t lifetime) : data(size), lifetime(lifetime) {}

	std::pair<int8_t, int8_t> get_move(const int8_t choice) const noexcept;
	void run() noexcept;
	void run(uint32_t start_x, uint32_t start_y, uint32_t value = 128) noexcept;

	void run_inc() noexcept;
	void run_inc(uint32_t start_x, uint32_t start_y, uint32_t increment = 1) noexcept;
};
