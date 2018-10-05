#ifndef VOODOO_ASSET_MANAGER_H_
#define VOODOO_ASSET_MANAGER_H_

#include <string>
#include <map>

namespace voodoo
{
	template<class T>
	class AssetManager
	{
	public:
		std::shared_ptr<T> Retrieve(std::string filename)
		{
			auto it = resources_.find(filename);

			if (it != resources_.end()) {
				return it->second;
			} else {
				auto resource = Load(filename);
				resources_.insert(std::pair<std::string, std::shared_ptr<T>>(filename, resource));
				return resource;
			}
		}

	protected:
		virtual std::shared_ptr<T> Load(std::string) = 0;

		void Unload(std::string filename)
		{
			auto it = resources_.find(filename);

			if (it == resources_.end()) {
				throw std::runtime_error("Trying to unload non-existing resource: \"" + filename + "\"");
			}
			else {
				resources_.erase(it);
			}
		}

	protected:
		std::map<std::string, std::shared_ptr<T>> resources_;
	};
}

#endif