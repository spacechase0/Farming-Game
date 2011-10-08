void SceneGame::LoadItems( const std::string& filename )
{
	std::fstream file( ( "res/items/" + filename ).c_str(), std::fstream::in );
	if ( !file )
	{
		std::cout << "Failed to load '" << file << "'." << std::endl;
		return;
	}

	std::string contents;
	while ( true )
	{
		std::string line;
		std::getline( file, line );
		if ( !file.eof() )
		{
			contents += line;
		}
		else
		{
			break;
		}
	}

	xml::Document doc;
	auto status = doc.Parse( contents );
	if ( !std::get< 0 >( status ) )
	{
		std::cout << "Failed to parse '" << file << "': " << std::get< 1 >( status ) << std::endl;
		return;
	}

	auto children = doc.GetRootNode().GetChildren();
	for ( auto it = children.begin(); it != children.end(); ++it )
	{
		xml::Node& node = ( * ( * it ) );
		std::string name = xml::GetAttribute( node, "name" ).GetValue();
		std::string desc = xml::GetAttribute( node, "desc" ).GetValue();
		std::string indexStr = xml::GetAttribute( node, "index" ).GetValue();
		std::string typeStr = xml::GetAttribute( node, "type" ).GetValue();

		item::Item::Type type = ToType( typeStr );
		size_t index = util::FromString< size_t >( indexStr );

		item::Item* item;
		switch ( type )
		{
			using namespace item;

			case Item::Type::Food:
				{
					std::string priceStr = xml::GetAttribute( node, "price" ).GetValue();
					size_t price = util::FromString< size_t >( priceStr );

					item = new Food( name, desc, index, price );
				}
				break;

			case Item::Type::Meal:
				{
					std::string priceStr = xml::GetAttribute( node, "price" ).GetValue();
					size_t price = util::FromString< size_t >( priceStr );

					item = new Food( name, desc, index, price );
					#warning TO DO: Make a class for Meal (since they have a seperate item file)
				}
				break;

			case Item::Type::Seed:
				{
					std::string crop = xml::GetAttribute( node, "crop" ).GetValue();
					item = new Seed( name, desc, index, crop );
				}
				break;

			case Item::Type::Tool:
				{
					std::string actionStr = xml::GetAttribute( node, "action" ).GetValue();
					std::string breakChanceStr = xml::GetAttribute( node, "breakchance" ).GetValue();

					Tool::Action action = ToAction( actionStr );
					float breakChance = util::FromString< float >( breakChanceStr );

					item = new Tool( name, desc, index, action, breakChance );
				}
				break;

			case Item::Type::Misc:
				{
					item = new Item( name, desc, index );
				}
				break;
		};
		itemDefs.insert( std::make_pair( name, boost::shared_ptr< item::Item >( item ) ) );
	}
}

item::Item::Type SceneGame::ToType( const std::string& str )
{
	using item::Item;
	if ( str == "food" )
	{
		return Item::Type::Food;
	}
	else if ( str == "meal" )
	{
		return Item::Type::Meal;
	}
	else if ( str == "seed" )
	{
		return Item::Type::Seed;
	}
	else if ( str == "tool" )
	{
		return Item::Type::Tool;
	}

	return Item::Type::Misc;
}

item::Tool::Action SceneGame::ToAction( const std::string& str )
{
	using item::Tool;
	if ( str == "dig" )
	{
		return Tool::Action::Dig;
	}
	else if ( str == "chop" )
	{
		return Tool::Action::Chop;
	}
	else if ( str == "fish" )
	{
		return Tool::Action::Fish;
	}

	return Tool::Action::None;
}
