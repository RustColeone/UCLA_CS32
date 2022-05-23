void removeEven(vector<int>& v)
{
	auto i = v.begin();
	auto last = v.begin();
	while (i != v.end())
	{
		if (*i % 2 == 0)
		{
			v.erase(i);
			i = last;
			//i--;
		}
		else {
			last = i;
			i++;
		}
	}
}