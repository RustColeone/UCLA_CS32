void removeBad(vector<Restaurant*>& v)
{
	for (auto i = v.begin(); i != v.end(); i++)
	{
		if ((*i)->stars() <= 2)
		{
			delete* i;
			i = v.erase(i);
			i--;
		}
	}
}