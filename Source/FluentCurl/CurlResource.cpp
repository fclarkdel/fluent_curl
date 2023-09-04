#include <FluentCurl/CurlResource.hpp>

namespace FluentCurl
{
CurlResource::CurlResource()
{
	std::scoped_lock scoped_lock(_global_lock);

	++_curl_resource_count;

	if(_curl_resource_count == 1)
		curl_global_init(CURL_GLOBAL_DEFAULT);
}
CurlResource::~CurlResource()
{
	std::scoped_lock scoped_lock(_global_lock);

	if(_curl_resource_count == 1)
		curl_global_cleanup();

	--_curl_resource_count;
}
}