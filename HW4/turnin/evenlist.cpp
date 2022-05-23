void removeEven(list<int>& li)
{
	auto i = li.begin();
	auto last = li.begin();
	while (i != li.end())
	{
		if (*i % 2 == 0)
		{
			li.erase(i);
			i = last;
			//i--;
		}
		else {
			last = i;
			i++;
		}
	}
}