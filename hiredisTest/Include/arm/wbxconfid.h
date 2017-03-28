
////////////////////////////////////////////
// class wbxConfId
// oliverz@isco.com
// 7/27/2015
///////////////////////////////////////////


#ifndef __WBX_CONF_ID_H__
#define __WBX_CONF_ID_H__


#include <string>

using namespace std;

#define WBXCONFID  wbxConfId

const int MAX_CONFID_LENGTH = 256;

typedef enum {
    WBX_CONFID_TYPE_UNKNOWN = 0,
    WBX_CONFID_TYPE_UINT32 = 1,
    WBX_CONFID_TYPE_STRING = 2

} WBX_CONFID_TYPE;

class wbxConfId {
public:

    wbxConfId();
	wbxConfId(unsigned int confid);
	wbxConfId(const char* confid);
    wbxConfId(bool is_string);
    wbxConfId(const wbxConfId& conf_id);
    virtual				~wbxConfId();
    wbxConfId&			operator=(unsigned int conf_id);
    wbxConfId&			operator=(const char* conf_id);
    wbxConfId&			operator=(const wbxConfId& conf_id);	
    bool				operator==(wbxConfId & conf_id) const;
    bool				operator > (unsigned int) const;
    bool				operator >= (unsigned int) const;
    bool				operator < (unsigned int) const;
    WBX_CONFID_TYPE		type() const;
    const string&		value() const;
	unsigned int		to_uint32() const;
	unsigned long long	to_longlong() const;
	const char*			to_string() const;
    bool				is_uint32() const;
	bool				is_string() const;
    int					length() const;
	void covert_to_string_confid();

private:
    WBX_CONFID_TYPE m_confid_type;
    string			m_conf_id;
	unsigned int	magic; // for invalid read check
};

struct Compare_confid {

    bool operator()(const wbxConfId & x, const wbxConfId & y) const {
			if(x.value() >= y.value())
				return 0;
		
			return 1;
    }
};

#endif
