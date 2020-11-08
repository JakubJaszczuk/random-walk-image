#include "RandomWalker.h"

std::pair<int8_t, int8_t> RandomWalker::get_move(const int8_t choice) const noexcept {
	switch (choice) {
		case 0: return {1, 0};
		case 1: return {-1, 0};
		case 2: return {0, 1};
		case 3: return {0, -1};
		default : return {0, 0};
	};
}

void RandomWalker::run() noexcept {
	run(data.width / 2, data.height / 2);
}

void RandomWalker::run(uint32_t start_x, uint32_t start_y, uint32_t value) noexcept {
	data.get(start_x, start_y) = value;
	for(uint32_t i = 0; i < lifetime; ++i) {
		const auto move = get_move(choice(rng));
		start_x += move.first;
		start_y += move.second;
		const auto location = data.get_safe(start_x, start_y);
		if(location != nullptr) {
			(*location) = value;
		}
	}
}

void RandomWalker::run_inc() noexcept {
	run_inc(data.width / 2, data.height / 2);
}

void RandomWalker::run_inc(uint32_t start_x, uint32_t start_y, uint32_t increment) noexcept {
	data.get(start_x, start_y) += increment;
	for(uint32_t i = 0; i < lifetime; ++i) {
		const auto move = get_move(choice(rng));
		start_x += move.first;
		start_y += move.second;
		const auto location = data.get_safe(start_x, start_y);
		if(location != nullptr) {
			(*location) += increment;
		}
	}
}

int main(int argc, char const *argv[]) {
	uint32_t resolution = 256;
	uint32_t lifetime = 10000;
	uint32_t count = 200;
	if(argc > 1) {
		resolution = std::atoi(argv[1]);
	}
	if(argc > 2) {
		lifetime = std::atoi(argv[2]);
	}
	if(argc > 3) {
		count = std::atoi(argv[3]);
	}

	RandomWalker rw(resolution, lifetime);
	for (uint32_t i = 0; i < count; ++i) {
		rw.run_inc();
	}
	// Zapisanie do pliku PPM
	fmt::print("Zapisuję do pliku.\n");
	std::ofstream ofs("img.ppm");
	ofs << "P3\n" << resolution << " " << resolution << "\n255\n";
	for(const auto& color : rw.data.get_buffer())
	{
		ofs << (int)color << " " << (int)color << " " << (int)color << " ";
	}
	return 0;
}
