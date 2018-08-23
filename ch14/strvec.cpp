#include"strvec.h"

void StrVec::push_back(const std::string& s)
{
	chk_n_alloc();
	alloc.construct(first_free++, s);
}

std::pair<std::string*, std::string*>
StrVec::alloc_n_copy(const std::string* b, const std::string* e)
{
	auto data = alloc.allocate(e - b);
	return{ data, std::uninitialized_copy(b, e, data) };
}

void StrVec::free()
{
	if (elements)
	{
		/*for (auto p = first_free; p != elements;)
			alloc.destroy(--p);*/
		std::for_each(elements, first_free, [this](std::string &s) {alloc.destroy(&s); });
		alloc.deallocate(elements, cap - elements);
	}
}
StrVec::StrVec(StrVec && sv) {
	elements = std::move(sv.elements), sv.elements = nullptr;
	first_free = std::move(sv.first_free), sv.first_free = nullptr;
	cap = std::move(sv.cap), sv.cap = nullptr;
}
StrVec& StrVec::operator=(StrVec && sv) {
	if (this != &sv) {
		free();
		delete elements;
		delete first_free;
		delete cap;
		elements = std::move(sv.elements), sv.elements = nullptr;
		first_free = std::move(sv.first_free), sv.first_free = nullptr;
		cap = std::move(sv.cap), sv.cap = nullptr;
	}
	return *this;
}

StrVec::StrVec(const StrVec& rhs)
{
	auto newdata = alloc_n_copy(rhs.begin(), rhs.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}
//ex13.40
StrVec::StrVec(std::initializer_list<std::string> il)
{
	range_initialize(il.begin(), il.end());
}

StrVec::~StrVec()
{
	free();
}

StrVec& StrVec::operator=(const StrVec& rhs)
{
	auto data = alloc_n_copy(rhs.begin(), rhs.end());
	free();
	elements = data.first;
	first_free = cap = data.second;
	return *this;
}

void StrVec::alloc_n_move(size_t new_cap)
{
	auto newdata = alloc.allocate(new_cap);
	auto dest = newdata;
	auto elem = elements;
	for (size_t i = 0; i != size(); ++i)
		alloc.construct(dest++, std::move(*elem++));
	free();
	elements = newdata;
	first_free = dest;
	cap = elements + new_cap;
}

void StrVec::reallocate()
{
	auto newcapacity = size() ? 2 * size() : 1;
	alloc_n_move(newcapacity);
}

//ex13.40
void StrVec::range_initialize(const std::string* first, const std::string* last)
{
	auto newdata = alloc_n_copy(first, last);
	elements = newdata.first;
	first_free = cap = newdata.second;
}

bool operator==(const StrVec & strv1, const StrVec & strv2)
{
	if (strv1.size() != strv2.size())	return false;
	for (auto it = strv1.elements, it2 = strv2.elements; it != strv1.first_free; it++, it2++)
		if (*it != *it2) return false;
	return true;
}

bool operator!=(const StrVec & strv1, const StrVec & strv2)
{
	return !(strv1 == strv2);
}
