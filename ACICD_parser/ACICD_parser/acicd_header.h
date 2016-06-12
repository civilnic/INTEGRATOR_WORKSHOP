#ifndef ACICD_HEADER_H
#define ACICD_HEADER_H

#include <vector>
#include <string>

const std::vector<std::string> EQUIPMENT_header={"EQUIPMENT","Equipment name","description","type","EMC Protection","Zone","FIN"};
const std::vector<std::string> CONNECTOR_header={"CONNECTOR","Connector Type","Connector Name","Connector Pin","Connector Pin Role","Connection Name","Line Type"};
const std::vector<std::string> AFDX_OUTPUT_VL_header={"AFDX_OUTPUT_VL","Physical Port Id","Physical Port Speed","Pin Name","AFDX Line EMC Protection","Network Id","Connector name","VL Identifier","VL name","Network Select","BAG","Max frame size","Number of sub VL","Sub VL Identifier","TX AFDX port Identifier","AFDX Port Master Name","AFDX Port type","port characteristic","IP frag allowed","AFDX port transmission type","Src IP address","Dest IP address","Src UDP address","Dest UDP address","Buffer Size"};
const std::vector<std::string> AFDX_OUTPUT_MESSAGE_header={"AFDX_OUTPUT_MESSAGE","Application name","Application description","Application type","Associated VL","Associated TX AFDX Port","Message name","Message description","Message ref doc","Message type","Message Protocol type","Message length","Global Spare length","Message Transmission rate","Port Refresh Rate","FDS name","FDS description","FDS length","FDS Spare length","FDS Address in the message","Functional Status name","FS description","FS address in the message","Parameter type","Parameter Local name","Local name Not produced","Local name Refresh Period","Local name Functional Attribute","Local name description","Parameter name","Parameter Keyword","Parameter description","Parameter Ref doc","Signal name","Signal type","Signal description","Signal ref doc","Signal Nb of bit","Signal address","Signal position","Bool True Definition","Bool False Definition","Bool True State","Bool False State","Bool logic","String length","String Format","Enumerate State","Enumerate Associated value","Float Operational min","Float Operational max","Float Operational unit","Float Operational accuracy","Float Coding type","Integer Operational min","Integer Operational max","Integer Operational unit","Integer Operational accuracy","Integer Coding type","Opaque size","Opaque length","Opaque IOM Corresponding Label"};
const std::vector<std::string> AFDX_INPUT_VL_header={"AFDX_INPUT_VL","Physical Port Id","Physical Port Speed","Pin Name","AFDX Line EMC Protection","Network Id","Connector name","VL Identifier","VL name","Network select","BAG","Max frame size","RMA","IC Active","Skew max","RX AFDX port Identifier","AFDX Port Master Name","AFDX Port type","port characteristic","IP frag allowed","Dest IP address","Dest UDP address","Buffer Size"};
const std::vector<std::string> AFDX_INPUT_MESSAGE_header={"AFDX_INPUT_MESSAGE","Application name","Application description","Application type","Associated VL","Associated RX AFDX Port","Message name","Message description","Message ref doc","Message type","Message Protocol type","Message length","Global Spare length","Message Transmission rate","Port Refresh Rate","FDS name","FDS description","FDS length","FDS Spare length","FDS Address in the message","Functional Status name","FS description","FS address in the message","Parameter type","Parameter Local name","Local name Not used","Local name Refresh Period","Local name Functional Attribute","Local name description","Parameter name","Parameter Keyword","Parameter description","Parameter Ref doc","Signal name","Signal type","Signal description","Signal ref doc","Signal Nb of bit","Signal address","Signal position","Bool True Definition","Bool False Definition","Bool True State","Bool False State","Bool logic","String length","String Format","Enumerate State","Enumerate Associated value","Float Operational min","Float Operational max","Float Operational unit","Float Operational accuracy","Float Coding type","Integer Operational min","Integer Operational max","Integer Operational unit","Integer Operational accuracy","Integer Coding type","Opaque size","Opaque length","Opaque IOM Corresponding Label"};
const std::vector<std::string> ICMP_header={"ICMP","dest IP","Reply VL id","Reply sub VL id","Reply VL Network Select","Reply VL BAG","Reply VL Max Frame size","Reply VL Buffer Size","Received VL Id","Received VL Network Select","Received VL BAG","Received VL Skew Max","Received VL Integrity Checking","RMA","Received VL Max Frame Size","Received VL Buffer Size"};
const std::vector<std::string> A429_OUTPUT_BUS_header={"A429_OUTPUT_BUS","Bus name","Bus description","Bus EMC protection","Bus speed","Bus Parity type","Bus Transmission rate","Connector type Pin name","Pin Role","Connector name","Connection name"};
const std::vector<std::string> A429_OUTPUT_LABEL_header={"A429_OUTPUT_LABEL","Application name","Application description","Application type","Associated Bus","Label name","Label Number","Port Refresh rate","Frame Frequency","Cycle frequency","Label description","Label type","SDI","val00Sdi","val01Sdi","val10Sdi","val11Sdi","SSM length","SSM value state 00","SSM value state 01","SSM value state 10","SSM value state 11","Protocol name","Protocol Position","Bit29 Sign id for value 0","Bit29 Sign id for value 1","Parameter type","Parameter Local name","Local name Not produced","Local name Refresh Period","Local name Functional Attribute","Local name description","Parameter name","Parameter Keyword","Parameter description","Parameter Ref doc","Signal name","Signal type","Signal description","Signal ref doc","Signal Nb of bit","Signal LSB","Signal MSB","Signal Transmit Order","Signal Start bit","Bool True Definition","Bool False Definition","Bool True State","Bool False State","Bool logic","String length","String Format","Enumerate State","Enumerate Associated value","Float Operational min","Float Operational max","Float Operational unit","Float Operational accuracy","Float Coding type","Float resolution","Float Scale Factor","Float offset","Float signed","Float Function non linear scale","Integer Operational min","Integer Operational max","Integer Operational unit","Integer Operational accuracy","Integer Coding type","Integer resolution","Integer Scale Factor","Integer offset","Integer signed","Integer Function non linear scale","Opaque max size","Opaque length"};
const std::vector<std::string> A429_INPUT_BUS_header={"A429_INPUT_BUS","Bus name","Bus description","Bus EMC protection","Bus speed","Bus Parity type","Bus Transmission rate","Connector type Pin name","Pin Role","Connector name","Connexion name"};
const std::vector<std::string> A429_INPUT_LABEL_header={"A429_INPUT_LABEL","Application name","Application description","Application type","Associated Bus","Label name","Label Number","Port Refresh rate","Label Refresh default","Frame Frequency","Cycle frequency","Label description","Label type","SDI","val00Sdi","val01Sdi","val10Sdi","val11Sdi","SSM length","SSM value state 00","SSM value state 01","SSM value state 10","SSM value state 11","Protocol name","Protocol Position","Bit29 Sign id for value 0","Bit29 Sign id for value 1","Parameter type","Parameter Local name","Local name Not used","Local name Refresh Period","Local name Functional Attribute","Local name description","Parameter name","Parameter Keyword","Parameter description","Parameter Ref doc","Signal name","Signal type","Signal description","Signal ref doc","Signal Nb of bit","Signal LSB","Signal MSB","Signal Transmit Order","Signal Start bit","Bool True Definition","Bool False Definition","Bool True State","Bool False State","Bool logic","String length","String Format","Enumerate State","Enumerate Associated value","Float Operational min","Float Operational max","Float Operational unit","Float Operational accuracy","Float Coding type","Float resolution","Float Scale Factor","Float offset","Float signed","Float Function non linear scale","Integer Operational min","Integer Operational max","Integer Operational unit","Integer Operational accuracy","Integer Coding type","Integer resolution","Integer Scale Factor","Integer offset","Integer signed","Integer Function non linear scale","Opaque max size","Opaque length"};
const std::vector<std::string> CAN_OUTPUT_BUS_header={"CAN_OUTPUT_BUS","Bus name","Bus description","Bus EMC protection","Bus Max Update Rate","Bus Transmission rate","Connector type Pin name","Pin Role","Connector name","Connexion name"};
const std::vector<std::string> CAN_OUTPUT_FRAME_header={"CAN_OUTPUT_FRAME","Application name","Application description","Application type","Associated Bus name","Frame name","Frame description","Frame Ref Doc","Frame Frequency","T timer","Tp","Ti","Tr","Min Load","Max Load"};
const std::vector<std::string> CAN_OUTPUT_MESSAGE_header={"CAN_OUTPUT_MESSAGE","Application name","Application description","Application type","Associated Bus","CAN Message name","Msg description","Msg Ref doc","Msg Protocol type","Msg Identifier","Msg Update rate","Event Message","Msg Payload length","Group name","Group Position","Msg Size","Port Refresh rate","Parameter type","Parameter Local name","Local name Not produced","Local name Refresh Period","Event Signal","Local name Functional Attribute","Local name description","Parameter name","Parameter Keyword","Parameter description","Parameter ref doc","Signal name","Signal type","Signal description","Signal ref doc","Signal Nb of bit","Signal LSB","Signal MSB","Signal Transmit Order","Signal Start bit","Bool True Definition","Bool False Definition","Bool True State","Bool False State","Bool logic","String length","String Format","Enumerate State","Enumerate Associated value","Float Operational min","Float Operational max","Float Operational unit","Float Operational accuracy","Float Coding type","Float resolution","Float Scale Factor","Float offset","Float signed","Float Function non linear scale","Integer Operational min","Integer Operational max","Integer Operational unit","Integer Operational accuracy","Integer Coding type","Integer resolution","Integer Scale Factor","Integer offset","Integer signed","Integer Function non linear scale","Opaque max size","Opaque length"};
const std::vector<std::string> CAN_INPUT_BUS_header={"CAN_INPUT_BUS","Bus name","Bus description","Bus EMC protection","Bus Max Update Rate","Bus Transmission rate","Connector type Pin name","Pin Role","Connector name","Connexion name"};
const std::vector<std::string> CAN_INPUT_FRAME_header={"CAN_INPUT_FRAME","Application name","Application description","Application type","Associated Bus name","Frame name","Frame description","Frame Ref Doc","Frame Frequency","T timer","Tp","Ti","Tr","Min Load","Max Load"};
const std::vector<std::string> CAN_INPUT_MESSAGE_header={"CAN_INPUT_MESSAGE","Application name","Application description","Application type","Associated Bus","CAN Message name","Msg description","Msg Ref doc","Msg Protocol type","Msg Identifier","Msg Update rate","Event Message","Msg Payload length","Group name","Group Position","Msg Size","Port Refresh rate","Msg Refresh default","Parameter type","Parameter Local name","Local name Not used","Local name Refresh Period","Event Signal","Local name Functional Attribute","Local name description","Parameter name","Parameter Keyword","Parameter description","Parameter ref doc","Signal name","Signal type","Signal description","Signal ref doc","Signal Nb of bit","Signal LSB","Signal MSB","Signal Transmit Order","Signal Start bit","Bool True Definition","Bool False Definition","Bool True State","Bool False State","Bool logic","String length","String Format","Enumerate State","Enumerate Associated value","Float Operational min","Float Operational max","Float Operational unit","Float Operational accuracy","Float Coding type","Float resolution","Float Scale Factor","Float offset","Float signed","Float Function non linear scale","Integer Operational min","Integer Operational max","Integer Operational unit","Integer Operational accuracy","Integer Coding type","Integer resolution","Integer Scale Factor","Integer offset","Integer signed","Integer Function non linear scale","Opaque max size","Opaque length"};
const std::vector<std::string> ANALOGUE_OUTPUT_LINE_header={"ANALOGUE_OUTPUT_LINE","Analog line name","line description","line EMC Protection","Connector type Pin name","Pin Role","Connector name","Connection name"};
const std::vector<std::string> ANALOGUE_OUTPUT_SIGNAL_header={"ANALOGUE_OUTPUT_SIGNAL","Application name","Application description","Application type","Associated Line name","Parameter type","Parameter Local name","Local name Not produced","Local name Refresh Period","Local name Functional Attribute","Local name description","Parameter name","Parameter Keyword","Parameter description","Parameter Ref doc","Keyword","Operational min","Operational max","Operational unit","Operational accuracy","Signal name","Signal description","IO type","Electrical accuracy","Scale Factor","offset","Engineering coding min","Engineering coding max","Engineering coding range unit","Electrical coding min","Electrical coding max","Electrical coding range unit","Excitation frequency","I Rating Min","I Rating Max","I Rating Unit","V Rating Min","V Rating Max","V Rating Unit","Function"};
const std::vector<std::string> ANALOGUE_INPUT_LINE_header={"ANALOGUE_INPUT_LINE","Line name","Line description","Line EMC Protection","Connector type Pin name","Pin Role","Connector name","Connection name"};
const std::vector<std::string> ANALOGUE_INPUT_SIGNAL_header={"ANALOGUE_INPUT_SIGNAL","Application name","Application description","Application type","Associated Line name","Parameter type","Parameter Local name","Local name Not used","Local name Refresh Period","Local name Functional Attribute","Local name description","Parameter name","Parameter Keyword","Parameter description","Parameter Ref doc","Keyword","Operational min","Operational max","Operational unit","Operational accuracy","Signal name","Signal description","IO type","Electrical accuracy","Scale Factor","offset","Engineering coding min","Engineering coding max","Engineering coding range unit","Electrical coding min","Electrical coding max","Electrical coding range unit","Excitation frequency","I Rating Min","I Rating Max","I Rating Unit","V Rating Min","V Rating Max","V Rating Unit","Function"};
const std::vector<std::string> DISCRETE_OUTPUT_LINE_header={"DISCRETE_OUTPUT_LINE","Discrete line name","line description","line EMC Protection","Connector type Pin name","Pin Role","Connector name","Connection name"};
const std::vector<std::string> DISCRETE_OUTPUT_SIGNAL_header={"DISCRETE_OUTPUT_SIGNAL","Application name","Application description","Application type","Line name","Parameter Local name","Local name Not produced","Local name Refresh Period","Local name Functional Attribute","Local name description","Parameter name","Parameter description","Parameter Ref doc","Keyword","True Definition","False Definition","Signal name","Signal description","IO type","True State","False State","Unit","Logic","Stabilization time","Default value","Min current range","Max current range","Unit current range"};
const std::vector<std::string> DISCRETE_INPUT_LINE_header={"DISCRETE_INPUT_LINE","Discrete line name","line description","line EMC Protection","Connector type Pin name","Pin Role","Connector name","Connection name"};
const std::vector<std::string> DISCRETE_INPUT_SIGNAL_header={"DISCRETE_INPUT_SIGNAL","Application name","Application description","Application type","Line name","Parameter Local name","Local name Not used","Local name Refresh Period","Local name Functional Attribute","Local name description","Parameter name","Parameter description","Parameter Ref doc","Keyword","True Definition","False Definition","Signal name","Signal description","IO type","True State","False State","Unit","Logic","Stabilization time","Default value","Min current range","Max current range","Unit current range"};
const std::vector<std::string> MIL1553_BUS_header={"MIL1553_BUS","Bus name","Bus description","Bus EMC protection","Bus Parity type","Bus Role","Bus Id","RT Address","MAF Name","MAF Id","MAF Description","MAF Number of MIF","MIF Duration","Bus select","Connector type pin name","Pin Role","Connector name","Connection name"};
const std::vector<std::string> MIL1553_MAF_DESCRIPTION_header={"MIL1553_MAF_DESCRIPTION","Bus name","MAF name","MIF Number","Application name","Message name","MIF Message start time"};
const std::vector<std::string> MIL1553_MESSAGE_header={"MIL1553_MESSAGE","Bus name","Application name","Application description","Application type","Message name","Msg description","Msg Ref doc","Message type","Message refresh timeout","TransmitReceiveMode","RT address","RT subaddress","RTtoRT Rx address","RTtoRT Rx subaddress","Mode code","Nb word","Functional Data name","Functional Data address","Functional Data length","Functional Data latency"};
const std::vector<std::string> MIL1553_OUTPUT_DATA_header={"MIL1553_OUTPUT_DATA","Application name","Message name","Functional data name","Parameter type","Parameter Local name","Local name Not produced","Local name Refresh Period","Local name Functional Attribute","Local name description","Parameter name","Parameter Keyword","Parameter description","Parameter ref doc","Signal name","Signal type","Signal description","Signal ref doc","Signal Nb of bit","Validity status Signal name","Signal MSB","Bool True Definition","Bool False Definition","Bool True State","Bool False State","Bool logic","String length","String Format","Enumerate State","Enumerate Associated value","Float Operational min","Float Operational max","Float Operational unit","Float Operational accuracy","Float Coding type","Float resolution","Float Scale Factor","Float offset","Float signed","Float Function non linear scale","Integer Operational min","Integer Operational max","Integer Operational unit","Integer Operational accuracy","Integer Coding type","Integer resolution","Integer Scale Factor","Integer offset","Integer signed","Integer Function non linear scale","Opaque max size","Opaque length"};
const std::vector<std::string> MIL1553_INPUT_DATA_header={"MIL1553_INPUT_DATA","Application name","Message name","Functional data name","Parameter type","Parameter Local name","Local name Not produced","Local name Refresh Period","Local name Functional Attribute","Local name description","Parameter name","Parameter Keyword","Parameter description","Parameter ref doc","Signal name","Signal type","Signal description","Signal ref doc","Signal Nb of bit","Validity status Signal name","Signal MSB","Bool True Definition","Bool False Definition","Bool True State","Bool False State","Bool logic","String length","String Format","Enumerate State","Enumerate Associated value","Float Operational min","Float Operational max","Float Operational unit","Float Operational accuracy","Float Coding type","Float resolution","Float Scale Factor","Float offset","Float signed","Float Function non linear scale","Integer Operational min","Integer Operational max","Integer Operational unit","Integer Operational accuracy","Integer Coding type","Integer resolution","Integer Scale Factor","Integer offset","Integer signed","Integer Function non linear scale","Opaque max size","Opaque length"};

const std::vector<std::vector<std::string>> vect_header={EQUIPMENT_header,CONNECTOR_header,AFDX_OUTPUT_VL_header,AFDX_OUTPUT_MESSAGE_header,AFDX_INPUT_VL_header,AFDX_INPUT_MESSAGE_header,ICMP_header
,A429_OUTPUT_BUS_header,A429_OUTPUT_LABEL_header,A429_INPUT_BUS_header,A429_INPUT_LABEL_header,CAN_OUTPUT_BUS_header,CAN_OUTPUT_FRAME_header,CAN_OUTPUT_MESSAGE_header,
CAN_INPUT_BUS_header,CAN_INPUT_FRAME_header,CAN_INPUT_MESSAGE_header,ANALOGUE_OUTPUT_LINE_header,ANALOGUE_OUTPUT_SIGNAL_header,ANALOGUE_INPUT_LINE_header,ANALOGUE_INPUT_SIGNAL_header,
DISCRETE_OUTPUT_LINE_header,DISCRETE_OUTPUT_SIGNAL_header,DISCRETE_INPUT_LINE_header,DISCRETE_INPUT_SIGNAL_header,MIL1553_BUS_header,MIL1553_MAF_DESCRIPTION_header,MIL1553_MESSAGE_header,MIL1553_OUTPUT_DATA_header,MIL1553_INPUT_DATA_header};

const std::string key_word_begin_data_section="Begin";
const std::string key_word_end_data_section="End";

enum class acicd_header_section {
    Comment=0,
    Begin,
    Header,
    Data,
    End
};

enum class acicd_data_section {
    UNDEF=0,
    EQUIPMENT,
    CONNECTOR,
    AFDX_OUTPUT_VL,
    AFDX_OUTPUT_MESSAGE,
    AFDX_INPUT_VL,
    AFDX_INPUT_MESSAGE,
    ICMP,
    A429_OUTPUT_BUS,
    A429_OUTPUT_LABEL,
    A429_INPUT_BUS,
    A429_INPUT_LABEL,
    CAN_OUTPUT_BUS,
    CAN_OUTPUT_FRAME,
    CAN_OUTPUT_MESSAGE,
    CAN_INPUT_BUS,
    CAN_INPUT_FRAME,
    CAN_INPUT_MESSAGE,
    ANALOGUE_OUTPUT_LINE,
    ANALOGUE_OUTPUT_SIGNAL,
    ANALOGUE_INPUT_LINE,
    ANALOGUE_INPUT_SIGNAL,
    DISCRETE_OUTPUT_LINE,
    DISCRETE_OUTPUT_SIGNAL,
    DISCRETE_INPUT_LINE,
    DISCRETE_INPUT_SIGNAL,
    MIL1553_BUS,
    MIL1553_MAF_DESCRIPTION,
    MIL1553_MESSAGE,
    MIL1553_OUTPUT_DATA,
    MIL1553_INPUT_DATA
};


#endif // ACICD_HEADER_H
