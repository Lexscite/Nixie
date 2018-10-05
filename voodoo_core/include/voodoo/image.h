#ifndef VOODOO_IMAGE_H_
#define VOODOO_IMAGE_H_

namespace voodoo
{
	struct Image
	{
	public:
		Image(const int& width, const int& height, const int& channels, unsigned char* data) :
			width(width),
			height(height),
			channels(channels),
			data(data)
		{}

		~Image()
		{
			if (data) {
				delete[] data;
			}
		}

	public:
		int width, height, channels;
		unsigned char* data;
	};
}

#endif