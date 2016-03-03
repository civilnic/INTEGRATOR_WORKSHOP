#ifndef DVP_CSV_DATA_H
#define DVP_CSV_DATA_H

#include <vector>
#include <string>
#include <boost/optional.hpp>
#include <boost/algorithm/string.hpp>

#include "acicd_header.h"

namespace dvp
{

class csv_data;

class csv_record
{
friend class csv_data;
	csv_data const& owner;
	std::vector<std::string> fields_;
	

	void add_field(std::string const& field) {
		fields_.push_back(field);
	}
	
public:	
	csv_record(csv_data const& owner_) : owner(owner_) {}
	typedef std::vector<std::string>::const_iterator const_iterator;
	const_iterator begin() const { return fields_.begin(); }
	const_iterator end() const { return fields_.end(); }

	std::string const& operator[](size_t i) const { return fields_[i]; }
	size_t size() const { return fields_.size(); }

	boost::optional<std::string const&> operator[](std::string const& header) const;
};

class csv_data
{
friend class csv_data_handler;
friend class acicd_data_handler;

	std::vector<csv_record> records_;
	std::vector<std::string> headers_;
    void new_record() { records_.emplace_back(*this); }
    void add_field(std::string const& field) { records_.back().add_field(field); }
public:
	typedef std::vector<csv_record>::const_iterator const_iterator;
	const_iterator begin() const { return records_.begin(); }
	const_iterator end() const { return records_.end(); }
	csv_record const& operator[](size_t i) { return records_[i]; }
	size_t size() const { return records_.size(); }	
	std::vector<std::string> const& headers() const { return headers_; }
};

boost::optional<std::string const&> csv_record::operator[](std::string const& header) const
{
	for(size_t i = 0; i < owner.headers().size(); ++i)
	{
		if(owner.headers()[i] == header)
			return fields_[i];
	}
	return boost::optional<std::string const&>();
}


class csv_data_handler
{
	bool has_headers_;
	csv_data& data_;
	bool at_beginning_of_line;
	bool at_first_line;
public:
	bool field_handler(std::string const& s)
	{
		if(at_first_line && has_headers_)
		{
			data_.headers_.push_back(s);
		}
		else
		{
			if(at_first_line)
				data_.headers_.push_back(std::string("header") + std::to_string(data_.headers_.size()));
			if(at_beginning_of_line)
			{
				data_.new_record();
				at_beginning_of_line = false;
			}
			data_.add_field(s);
		}
		return true;
	}
	bool end_line_handler()
	{
		at_beginning_of_line = true;
		at_first_line = false;
		return true;
	}

	template<typename parser_>
	csv_data_handler(csv_data& data, bool has_header_line, parser_& parser) :
		data_(data),
		has_headers_(has_header_line),
		at_beginning_of_line(true),
		at_first_line(true)
	{
		parser.field_handler = [this](std::string const& s) { return this->field_handler(s); };
		parser.end_line_handler = [this]() { return this->end_line_handler(); };
	}
		
};



class acicd_data_handler
{
    bool has_headers_;
    csv_data& data_;
    bool at_beginning_of_line;
    bool at_first_line;
    acicd_header_section acicd_localization;
    acicd_data_section acicd_section_id;
    std::vector<std::string> section_name;

public:

    bool comment_handler(std::string const& s)
    {
        boost::split(section_name,s, boost::is_any_of(";"));
 //      std::cout <<"section_name:" << std::endl;
 //     std::cout <<section_name[0] << std::endl;
        //        printf("acicd_localization: %d\n",acicd_localization);
        //       printf("acicd_data_section: %d\n",acicd_section_id);
        //std::cout <<section_name << std::endl;

        if(acicd_localization==acicd_header_section::Begin)
        {
           // section_name.push_back(s);

            for(std::vector<std::vector<std::string>>::const_iterator it_headers=vect_header.begin();it_headers!=vect_header.end();++it_headers)
            {
                std::vector<std::string>::const_iterator it_column_name=(*it_headers).begin();

//std::cout <<section_name[0].compare(*it_column_name) << std::endl;
                if(section_name[0].compare(*it_column_name)==0)
                {
                    std::cout <<"avant test: " << std::endl;
                    std::cout <<*it_column_name << std::endl;
                    std::cout <<"section_name: " << std::endl;
                   std::cout <<section_name[0] << std::endl;
                     std::cout <<"entete: " << std::endl;
                     std::cout <<*it_column_name << std::endl;
                     std::cout <<"indice: " << std::endl;
                     std::cout <<it_headers - vect_header.begin()+1<< std::endl;
                     acicd_section_id=acicd_data_section(it_headers - vect_header.begin()+1);
                      printf("acicd_data_section: %d\n",acicd_section_id);
                }
             //   for(std::vector<std::string>::const_iterator it_column_name=(*it_headers).begin();it_column_name!=(*it_headers).end();++it_column_name)
           //     {
            //        std::cout <<*it_column_name << std::endl;
           //     }


            }

        }

        if(at_beginning_of_line)
        {

            if(section_name[0].compare(key_word_begin_data_section)==0)
            {
                acicd_localization=acicd_header_section::Begin;
                std::cout <<"passage a begin" << std::endl;
                return true;
            }
            else if(section_name[0].compare(key_word_end_data_section)==0)
            {
                acicd_localization=acicd_header_section::End;
                std::cout <<"passage a end" << std::endl;
                return true;
            }

            if(acicd_localization==acicd_header_section::Begin)
            {
                acicd_localization=acicd_header_section::Header;
                std::cout <<"passage a header" << std::endl;
                return true;
            }

            if(acicd_localization==acicd_header_section::Header)
            {
                acicd_localization=acicd_header_section::Data;
              //  section_name.clear();
                std::cout <<"passage a data" << std::endl;
                return true;
            }

            at_beginning_of_line = false;
        }



        return true;
    }

    bool field_handler(std::string const& s)
    {
    //    std::cout <<"data:" << std::endl;
    //    std::cout <<s << std::endl;
        if(at_first_line && has_headers_)
        {
            data_.headers_.push_back(s);
        }
        else
        {
            if(at_first_line)
                data_.headers_.push_back(std::string("header") + std::to_string(data_.headers_.size()));
            if(at_beginning_of_line)
            {
                data_.new_record();
                at_beginning_of_line = false;
            }
            data_.add_field(s);
        }
        return true;
    }
    bool end_line_handler()
    {
        at_beginning_of_line = true;
        at_first_line = false;
        return true;
    }

    template<typename parser_>
    acicd_data_handler(csv_data& data, bool has_header_line, parser_& parser) :
        data_(data),
        has_headers_(has_header_line),
        at_beginning_of_line(true),
        acicd_localization(acicd_header_section::Comment),
        acicd_section_id(acicd_data_section::UNDEF),
        at_first_line(true)
    {
        parser.comment_handler = [this](std::string const& s) { return this->comment_handler(s); };
        parser.field_handler = [this](std::string const& s) { return this->field_handler(s); };
        parser.end_line_handler = [this]() { return this->end_line_handler(); };
    }

};
}

#endif
