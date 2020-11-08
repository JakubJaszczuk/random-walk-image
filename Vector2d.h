#include <vector>
#include <optional>

template <typename T>
struct Vector2d {

	using data_t = T;
	std::vector<T> data;
	int32_t width;
	int32_t height;

	Vector2d(const uint32_t size = 10);
	Vector2d(const uint32_t width, const uint32_t height);
	const std::vector<T>& get_buffer() const;
	void set(const uint32_t x, const uint32_t y, const T& value);
	void set_safe(const uint32_t x, const uint32_t y, const T& value);
	T& get(const uint32_t x, const uint32_t y) const;
	T& get(const uint32_t x, const uint32_t y);
	T* get_safe(const int32_t x, const int32_t y);
	T& get_safe_or_default(const int32_t x, const int32_t y, const T& def) const;
	std::pair<uint32_t, uint32_t> convert_index_to_2d(const int32_t index) const;
	int32_t convert_to_index(const int32_t x, const int32_t y) const;
};

template <typename T>
inline Vector2d<T>::Vector2d(const uint32_t size) : data(size * size), width(size), height(size) {}

template <typename T>
inline Vector2d<T>::Vector2d(const uint32_t width, const uint32_t height) : data(width * height), width(width), height(height) {}

template <typename T>
inline const std::vector<T>& Vector2d<T>::get_buffer() const {
	return data;
}

template <typename T>
inline void Vector2d<T>::set(const uint32_t x, const uint32_t y, const T& value) {
	data[convert_to_index(x, y)] = value;
}

template <typename T>
inline void Vector2d<T>::set_safe(const uint32_t x, const uint32_t y, const T& value) {
	if (!(x < 0 || x >= width || y < 0 || y >= height)) {
		data[convert_to_index(x, y)] = value;
	}
}

template <typename T>
inline T& Vector2d<T>::get(const uint32_t x, const uint32_t y) const {
	return data[convert_to_index(x, y)];
}

template <typename T>
inline T& Vector2d<T>::get(const uint32_t x, const uint32_t y) {
	return data[convert_to_index(x, y)];
}

template <typename T>
inline T* Vector2d<T>::get_safe(const int32_t x, const int32_t y) {
	if(x < 0 || x >= width || y < 0 || y >= height) return nullptr;
	else return &data[convert_to_index(x, y)];
}

template <typename T>
inline T& Vector2d<T>::get_safe_or_default(const int32_t x, const int32_t y, const T& def) const {
	if(x < 0 || x >= width || y < 0 || y >= height) return def;
	else return data[convert_to_index(x, y)];
}

template <typename T>
inline std::pair<uint32_t, uint32_t> Vector2d<T>::convert_index_to_2d(const int32_t index) const {
	return std::pair(index % width, index / width);
}

template <typename T>
inline int32_t Vector2d<T>::convert_to_index(const int32_t x, const int32_t y) const {
	return x + width * y;
}
