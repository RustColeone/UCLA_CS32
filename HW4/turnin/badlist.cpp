void removeBad(list<Restaurant*>& li)
{
	for (auto i = li.begin(); i != li.end(); i++)
	{
		if ((*i)->stars() <= 2)
		{
			delete* i;
			i = li.erase(i);
			i--;
		}
	}
}