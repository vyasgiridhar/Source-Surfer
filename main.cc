
int level = 0;
#include <giomm.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <thread>

void print(std::string sentence){
	std::cout<<sentence;
}

void search_word(std::string file,std::string search){
	std::string words;
	int flag;
	try{
		std::ifstream f(file.c_str());
		while(getline(f,words)){

			if(!words.find(search)){
				std::cout<<"found @ "<<file<<"\n"<<words<<std::endl;
			} 
		}
		f.close();
	}catch(...){
		return ;
	}
return ;
		
}

int start(std::string name, std::string search)
{
  Gio::init();
  a:
  try
  {
    auto directory = Gio::File::create_for_path(name);
    if(!directory)
      std::cerr << "Gio::File::create_for_path() returned an empty RefPtr." << std::endl;

    auto enumerator = directory->enumerate_children();
    if(!enumerator)
      std::cerr << "Gio::File::enumerate_children() returned an empty RefPtr." << std::endl;
    auto file_info = enumerator->next_file();
    while(file_info)
    {
    //  std::cout << "file: " << file_info->get_name() << std::endl;
      if(file_info->get_file_type( )==Gio::FILE_TYPE_DIRECTORY&&file_info->get_name()[0]!='.'){

      	std::thread st(start,directory->get_child((file_info->get_name()))->get_path(),search);
      	st.detach();
        level++;

      }
      std::string file = (directory->get_child((file_info->get_name())))->get_path();
      if(file_info->get_file_type()==Gio::FILE_TYPE_REGULAR){

       std::thread searcher(search_word,file,search);
       searcher.detach();

      }
      file_info = enumerator->next_file();
    }

  }
  catch(const Glib::Exception& ex)
  {
   // std::cerr << "Exception caught: " << ex.what() << std::endl; 
  	goto a;
  }


  return 0;
}

int main(int argc,char** argv){
	
	std::string x= argv[2];
	std::cout<<"Starting @"<<argv[1];
	start(argv[1],x);

return 0;
}