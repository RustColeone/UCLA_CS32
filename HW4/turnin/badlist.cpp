void removeBad(list<Restaurant*>& li)
{
    auto i = li.begin();
	auto last = li.begin();
	while (i != li.end())
	{
		if ((*i)->stars() <= 2)
		{
            delete * i;
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