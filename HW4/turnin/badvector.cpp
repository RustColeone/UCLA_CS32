void removeBad(vector<Restaurant*>& v)
{
    auto i = v.begin();
	auto last = v.begin();
	while (i != v.end())
	{
		if ((*i)->stars() <= 2)
		{
            delete * i;
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