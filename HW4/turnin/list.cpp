void listAll(const Domain* d, string path) // two-parameter overload
{
    //end recursion
    if (d->subdomains().empty())
	{
        //when the subdomains are empty
        //this is the only domain now of recursion
		cout << path << endl;
		return;
	}
    else if (path != ""){
		path = '.' + path;
    }
    //for each in subdomain
    //print them
	for (auto i = d->subdomains().begin(); i != d->subdomains().end(); i++){
        listAll(*i, (*i)->label() + path);
    }
}