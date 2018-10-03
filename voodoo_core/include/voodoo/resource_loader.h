#ifndef VOODOO_RESOURCE_LOADER_H_
#define VOODOO_RESOURCE_LOADER_H_

#include <string>
#include <map>

namespace voodoo
{
	template<class T>
	class ResourceLoader
	{
	public:
		std::shared_ptr<T> Load(std::string file_path)
		{
			auto it = resources_.find(file_path);

			if (it != resources_.end()) {
				return it->second;
			} else {
				auto resource = ProcessFile(file_path);
				resources_.insert(std::pair<std::string, std::shared_ptr<T>>(file_path, resource));
				return resource;
			}
		}

		void Unload(std::string file_path)
		{
			auto it = resources_.find(file_path);

			if (it == resources_.end()) {
				throw std::runtime_error("Trying to unload non-existing resource: \"" + file_path + "\"");
			} else {
				resources_.erase(it);
			}
		}

	protected:
		virtual std::shared_ptr<T> ProcessFile(std::string) = 0;

	protected:
		std::map<std::string, std::shared_ptr<T>> resources_;
	};
}

#endif