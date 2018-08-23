#ifndef EX12_19_H
#define EX12_19_H

#include <string>
#include <vector>
#include <initializer_list>
#include <memory>
#include <stdexcept>

using std::vector; using std::string;

class StrBlobPtr;

class StrBlob
{
	friend bool operator==(const StrBlob&,const StrBlob&);
	friend bool operator!=(const StrBlob&, const StrBlob&);
public:
	using size_type = vector<string>::size_type;
	friend class StrBlobPtr;

	StrBlobPtr begin();
	StrBlobPtr end();

	StrBlob() : data(std::make_shared<vector<string>>()) {}
	StrBlob(std::initializer_list<string> il) : data(std::make_shared<vector<string>>(il)) {}

	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }

	void push_back(const string& s) { data->push_back(s); }
	void pop_back()
	{
		check(0, "pop_back on empty StrBlob");
		data->pop_back();
	}

	std::string& front()
	{
		check(0, "front on empty StrBlob");
		return data->front();
	}

	std::string& back()
	{
		check(0, "back on empty StrBlob");
		return data->back();
	}

	const std::string& front() const
	{
		check(0, "front on empty StrBlob");
		return data->front();
	}
	const std::string& back() const
	{
		check(0, "back on empty StrBlob");
		return data->back();
	}

private:
	void check(size_type i, const string& msg) const
	{
		if (i >= data->size())
			throw std::out_of_range(msg);
	}

private:
	std::shared_ptr<vector<string>> data;
};
bool operator==(const StrBlob&, const StrBlob&);
bool operator!=(const StrBlob&, const StrBlob&);


class StrBlobPtr
{
	friend bool operator==(const StrBlobPtr&, const StrBlobPtr&);
	friend bool operator!=(const StrBlobPtr&, const StrBlobPtr&);

public:
	StrBlobPtr() :curr(0) {}
	StrBlobPtr(StrBlob &a, size_t sz = 0) :wptr(a.data), curr(sz) {}
	bool operator!=(const StrBlobPtr& p) { return p.curr != curr; }
	string& deref() const
	{
		auto p = check(curr, "dereference past end");
		return (*p)[curr];
	}
	StrBlobPtr& incr()
	{
		check(curr, "increment past end of StrBlobPtr");
		++curr;
		return *this;
	}

private:
	std::shared_ptr<vector<string>> check(size_t i, const string &msg) const
	{
		auto ret = wptr.lock();
		if (!ret) throw std::runtime_error("unbound StrBlobPtr");
		if (i >= ret->size()) throw std::out_of_range(msg);
		return ret;
	}
	std::weak_ptr<vector<string>> wptr;
	size_t curr;
};

bool operator==(const StrBlobPtr&, const StrBlobPtr&);
bool operator!=(const StrBlobPtr&, const StrBlobPtr&);


StrBlobPtr StrBlob::begin()
{
	return StrBlobPtr(*this);
}
StrBlobPtr StrBlob::end()
{
	return StrBlobPtr(*this, data->size());
}

bool operator==(const StrBlob & strb1, const StrBlob & strb2)
{
	return strb1.data == strb2.data ? true : false;
}

bool operator!=(const StrBlob & strb1, const StrBlob &strb2)
{
	return strb1.data != strb2.data ? true : false;
}

bool operator==(const StrBlobPtr &sbp1, const StrBlobPtr &sbp2)
{
	return sbp1.curr == sbp2.curr && sbp1.deref == sbp2.deref;
}

bool operator!=(const StrBlobPtr &sbp1, const StrBlobPtr &sbp2)
{
	return sbp1.curr != sbp2.curr && sbp1.deref != sbp2.deref;
}

#endif

