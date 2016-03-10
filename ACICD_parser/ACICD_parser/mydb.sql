-- Creator       : MySQL Workbench 6.3.6 /ExportSQLServer plugin 2015.07.30
-- Author        : nbonnet
-- Caption       : New Model
-- Project       : Name of the project
-- Changed       : 2016-03-10 23:18
-- Created       : 2016-01-06 13:36

-- Schema: mydb 
CREATE SCHEMA  [mydb];

CREATE TABLE [mydb].[Signals](
 [Id] INTEGER CONSTRAINT [pk_Signals] PRIMARY KEY  NOT NULL,  
 [Name] VARCHAR( 45 ) NULL,  
 [Init] NUMERIC NULL
);


CREATE TABLE [mydb].[Data_Type](
 [id] INTEGER CONSTRAINT [pk_Data_Type] PRIMARY KEY  NOT NULL,  
 [Name] VARCHAR( 45 ) NULL
);


CREATE TABLE [mydb].[Operators](
 [id] INTEGER CONSTRAINT [pk_Operators] PRIMARY KEY  NOT NULL,  
 [Name] VARCHAR( 45 ) NULL
);


CREATE TABLE [mydb].[Com_Format](
 [id] INTEGER CONSTRAINT [pk_Com_Format] PRIMARY KEY  NOT NULL,  
 [Name] VARCHAR( 45 ) NULL
);


CREATE TABLE [mydb].[Com_Mode](
 [id] INTEGER CONSTRAINT [pk_Com_Mode] PRIMARY KEY  NOT NULL,  
 [Name] VARCHAR( 45 ) NULL
);


CREATE TABLE [mydb].[Interface_level](
 [id] INTEGER CONSTRAINT [pk_Interface_level] PRIMARY KEY  NOT NULL,  
 [Name] VARCHAR( 45 ) NULL
);


CREATE TABLE [mydb].[status](
 [id] INTEGER CONSTRAINT [pk_status] PRIMARY KEY  NOT NULL,  
 [Name] VARCHAR( 45 ) NULL
);


CREATE TABLE [mydb].[Unit](
 [id] INTEGER CONSTRAINT [pk_Unit] PRIMARY KEY  NOT NULL,  
 [Name] VARCHAR( 45 ) NULL
);


CREATE TABLE [mydb].[flot](
 [id] INTEGER CONSTRAINT [pk_flot] PRIMARY KEY  NOT NULL,  
 [filename] VARCHAR( 45 ) NULL
);


CREATE TABLE [mydb].[MICD](
 [id] INTEGER CONSTRAINT [pk_MICD] PRIMARY KEY  NOT NULL,  
 [Name] VARCHAR( 45 ) NULL,  
 [Path] VARCHAR( 45 ) NULL
);


CREATE TABLE [mydb].[EQUIPMENT](
 [id] INTEGER CONSTRAINT [pk_EQUIPMENT] PRIMARY KEY  NOT NULL,  
 [Name] VARCHAR( 45 ) NULL,  
 [Description] VARCHAR( 45 ) NULL,  
 [Type] VARCHAR( 45 ) NULL,  
 [EMC Protection] VARCHAR( 45 ) NULL,  
 [Zone] VARCHAR( 45 ) NULL
);


CREATE TABLE [mydb].[Connector_Line_type](
 [id] INTEGER CONSTRAINT [pk_Connector_Line_type] PRIMARY KEY  NOT NULL,  
 [Name] VARCHAR( 45 ) NULL
);


CREATE TABLE [mydb].[Connector_Pin_Role](
 [id] INTEGER CONSTRAINT [pk_Connector_Pin_Role] PRIMARY KEY  NOT NULL,  
 [Name] VARCHAR( 45 ) NULL
);


CREATE TABLE [mydb].[Connection_Name](
 [id] INTEGER CONSTRAINT [pk_Connection_Name] PRIMARY KEY  NOT NULL,  
 [Name] VARCHAR( 45 ) NULL
);


CREATE TABLE [mydb].[AFDX_port_transmission_type](
 [id] INTEGER CONSTRAINT [pk_AFDX_port_transmission_type] PRIMARY KEY  NOT NULL,  
 [Name] VARCHAR( 9 ) NULL
);


CREATE TABLE [mydb].[AFDX_port_type](
 [id] INTEGER CONSTRAINT [pk_AFDX_port_type] PRIMARY KEY  NOT NULL,  
 [Type] VARCHAR( 45 ) NULL
);


CREATE TABLE [mydb].[AFDX_port_characteristic](
 [id] INTEGER CONSTRAINT [pk_AFDX_port_characteristic] PRIMARY KEY  NOT NULL,  
 [characteristic] VARCHAR( 9 ) NULL
);


CREATE TABLE [mydb].[AFDX_application](
 [id] INTEGER CONSTRAINT [pk_AFDX_application] PRIMARY KEY  NOT NULL,  
 [name] VARCHAR( 45 ) NULL,  
 [type] VARCHAR( 45 ) NULL,  
 [description] VARCHAR( 45 ) NULL
);


CREATE TABLE [mydb].[AFDX_Message_type](
 [id] INTEGER CONSTRAINT [pk_AFDX_Message_type] PRIMARY KEY  NOT NULL,  
 [message_type] VARCHAR( 45 ) NULL
);


CREATE TABLE [mydb].[AFDX_signal_type](
 [id] INTEGER CONSTRAINT [pk_AFDX_signal_type] PRIMARY KEY  NOT NULL,  
 [type] VARCHAR( 15 ) NULL
);


CREATE TABLE [mydb].[AFDX_signal_BOOL_caract](
 [id] INTEGER CONSTRAINT [pk_AFDX_signal_BOOL_caract] PRIMARY KEY  NOT NULL,  
 [TRUE_def] VARCHAR( 10 ) NULL,  
 [FALSE_def] VARCHAR( 10 ) NULL,  
 [TRUE_state] BIT NULL,  
 [FALSE_state] BIT NULL,  
 [Logic] VARCHAR( 45 ) NULL
);


CREATE TABLE [mydb].[AFDX_signal_String_caract](
 [id] INTEGER CONSTRAINT [pk_AFDX_signal_String_caract] PRIMARY KEY  NOT NULL,  
 [lenght] VARCHAR( 45 ) NULL,  
 [format] VARCHAR( 45 ) NULL
);


CREATE TABLE [mydb].[AFDX_Enumerate_caract](
 [id] INTEGER CONSTRAINT [pk_AFDX_Enumerate_caract] PRIMARY KEY  NOT NULL,  
 [state] VARCHAR( 45 ) NULL,  
 [associated_value] VARCHAR( 45 ) NULL
);


CREATE TABLE [mydb].[Coding_type](
 [id] INTEGER CONSTRAINT [pk_Coding_type] PRIMARY KEY  NOT NULL,  
 [type] VARCHAR( 45 ) NULL
);


CREATE TABLE [mydb].[AFDX_signal_INT_caract](
 [id] INTEGER CONSTRAINT [pk_AFDX_signal_INT_caract] PRIMARY KEY  NOT NULL,  
 [min] INTEGER NULL,  
 [max] INTEGER NULL,  
 [Unit_id] INTEGER NOT NULL,  
 [accuray] INTEGER NULL,  
 [Coding_type_id] INTEGER NOT NULL,  
  CONSTRAINT [fk_AFDX_signal_INT_caract_Unit1] 
  FOREIGN KEY([Unit_id])
    REFERENCES [Unit] ( [id] ),  
  CONSTRAINT [fk_AFDX_signal_INT_caract_Coding_type1] 
  FOREIGN KEY([Coding_type_id])
    REFERENCES [Coding_type] ( [id] )
);
CREATE INDEX [fk_AFDX_signal_INT_caract_Unit1_idx] ON [mydb].[AFDX_signal_INT_caract] ([Unit_id]);
CREATE INDEX [fk_AFDX_signal_INT_caract_Coding_type1_idx] ON [mydb].[AFDX_signal_INT_caract] ([Coding_type_id]);


CREATE TABLE [mydb].[AFDX_signal_opaque_caract](
 [id] INTEGER CONSTRAINT [pk_AFDX_signal_opaque_caract] PRIMARY KEY  NOT NULL,  
 [size] INTEGER NULL,  
 [lenght] INTEGER NULL,  
 [IOM_corresponding_label] INTEGER NULL,  
 [Corresponding_label] INTEGER NULL
);


CREATE TABLE [mydb].[AFDX_RX_port](
 [id] INTEGER CONSTRAINT [pk_AFDX_RX_port] PRIMARY KEY  NOT NULL,  
 [Identifier] INTEGER NULL,  
 [Master_Name] VARCHAR( 45 ) NULL,  
 [Type] INTEGER NULL,  
 [characteristic] INTEGER NULL,  
 [transmission_type] INTEGER NULL,  
 [EQUIPMENT] INTEGER NOT NULL,  
 [Dest_IP_Adress] VARCHAR( 15 ) NULL,  
 [Dest_UDP_Adress] INTEGER NULL,  
 [Buffersize] INTEGER NULL,  
 [IP_frag_allowed] BIT NULL,  
  CONSTRAINT [Type0] 
  FOREIGN KEY([Type])
    REFERENCES [AFDX_port_type] ( [id] ),  
  CONSTRAINT [characteristic0] 
  FOREIGN KEY()
    REFERENCES [AFDX_port_characteristic] (  ),  
  CONSTRAINT [transmission_type0] 
  FOREIGN KEY([transmission_type])
    REFERENCES [AFDX_port_transmission_type] ( [id] ),  
  CONSTRAINT [fk_AFDX_TX_port_EQUIPMENT10] 
  FOREIGN KEY([EQUIPMENT])
    REFERENCES [EQUIPMENT] ( [id] )
);
CREATE INDEX [Type_idx] ON [mydb].[AFDX_RX_port] ([Type]);
CREATE INDEX [transmission_type_idx] ON [mydb].[AFDX_RX_port] ([transmission_type]);
CREATE INDEX [fk_AFDX_TX_port_EQUIPMENT1_idx] ON [mydb].[AFDX_RX_port] ([EQUIPMENT]);


CREATE TABLE [mydb].[Models](
 [id] INTEGER NOT NULL,  
 [Name] VARCHAR( 45 ) NULL,  
 [Occurence] INTEGER NULL,  
 [Micd] INTEGER NOT NULL, 
 CONSTRAINT [pk_Models] PRIMARY KEY([id],[Micd]),  
  CONSTRAINT [Micd] 
  FOREIGN KEY([Micd])
    REFERENCES [MICD] ( [id] )
    ON DELETE SET NULL
);
CREATE INDEX [Micd_idx] ON [mydb].[Models] ([Micd]);


CREATE TABLE [mydb].[ACICD](
 [id] INTEGER CONSTRAINT [pk_ACICD] PRIMARY KEY  NOT NULL,  
 [Name] VARCHAR( 45 ) NULL,  
 [Path] VARCHAR( 45 ) NULL,  
 [Micd] INTEGER NULL,  
 [Equipment] INTEGER NULL,  
 [Version] VARCHAR( 45 ) NULL,  
  CONSTRAINT [Equipment] 
  FOREIGN KEY([Equipment])
    REFERENCES [EQUIPMENT] ( [id] )
);
CREATE INDEX [Equipment_idx] ON [mydb].[ACICD] ([Equipment]);


CREATE TABLE [mydb].[jointure_MICD_ACICD](
 [micd] INTEGER CONSTRAINT [pk_jointure_MICD_ACICD] PRIMARY KEY  NOT NULL,  
 [acicd] INTEGER NULL,  
  CONSTRAINT [micd] 
  FOREIGN KEY([micd])
    REFERENCES [MICD] ( [id] ),  
  CONSTRAINT [acicd] 
  FOREIGN KEY([acicd])
    REFERENCES [ACICD] ( [id] )
);
CREATE INDEX [acicd_idx] ON [mydb].[jointure_MICD_ACICD] ([acicd]);


CREATE TABLE [mydb].[CONNECTOR](
 [id] INTEGER CONSTRAINT [pk_CONNECTOR] PRIMARY KEY  NOT NULL,  
 [Equipment] INTEGER NULL,  
 [ACICD] INTEGER NULL,  
 [Type] VARCHAR( 45 ) NULL,  
 [Name] VARCHAR( 45 ) NULL,  
 [Pin] VARCHAR( 45 ) NULL,  
 [Pin_Role] INTEGER NULL,  
 [Connection_Name] INTEGER NULL,  
 [Line_Type] INTEGER NULL,  
 [Speed] INTEGER NULL,  
 [NetworkId] VARCHAR( 3 ) NULL,  
  CONSTRAINT [Equipment] 
  FOREIGN KEY([Equipment])
    REFERENCES [EQUIPMENT] ( [id] ),  
  CONSTRAINT [ACICD] 
  FOREIGN KEY([ACICD])
    REFERENCES [ACICD] ( [id] ),  
  CONSTRAINT [Pin_Role] 
  FOREIGN KEY([Pin_Role])
    REFERENCES [Connector_Pin_Role] ( [id] ),  
  CONSTRAINT [Line_Type] 
  FOREIGN KEY([Line_Type])
    REFERENCES [Connector_Line_type] ( [id] ),  
  CONSTRAINT [Connection_Name] 
  FOREIGN KEY([Connection_Name])
    REFERENCES [Connection_Name] ( [id] )
);
CREATE INDEX [Equipment_idx] ON [mydb].[CONNECTOR] ([Equipment]);
CREATE INDEX [ACICD_idx] ON [mydb].[CONNECTOR] ([ACICD]);
CREATE INDEX [Pin_Role_idx] ON [mydb].[CONNECTOR] ([Pin_Role]);
CREATE INDEX [Line_Type_idx] ON [mydb].[CONNECTOR] ([Line_Type]);
CREATE INDEX [Connection_Name_idx] ON [mydb].[CONNECTOR] ([Connection_Name]);


CREATE TABLE [mydb].[AFDX_TX_port](
 [id] INTEGER CONSTRAINT [pk_AFDX_TX_port] PRIMARY KEY  NOT NULL,  
 [Identifier] INTEGER NULL,  
 [Master_Name] VARCHAR( 45 ) NULL,  
 [Type] INTEGER NULL,  
 [characteristic] INTEGER NULL,  
 [transmission_type] INTEGER NULL,  
 [EQUIPMENT] INTEGER NOT NULL,  
 [Src_IP_Adress] VARCHAR( 15 ) NULL,  
 [Dest_IP_Adress] VARCHAR( 15 ) NULL,  
 [Src_UDP_Adress] INTEGER NULL,  
 [Dest_UDP_Adress] INTEGER NULL,  
 [Buffersize] INTEGER NULL,  
 [IP_frag_allowed] BIT NULL,  
  CONSTRAINT [Type] 
  FOREIGN KEY([Type])
    REFERENCES [AFDX_port_type] ( [id] ),  
  CONSTRAINT [characteristic] 
  FOREIGN KEY()
    REFERENCES [AFDX_port_characteristic] (  ),  
  CONSTRAINT [transmission_type] 
  FOREIGN KEY([transmission_type])
    REFERENCES [AFDX_port_transmission_type] ( [id] ),  
  CONSTRAINT [fk_AFDX_TX_port_EQUIPMENT1] 
  FOREIGN KEY([EQUIPMENT])
    REFERENCES [EQUIPMENT] ( [id] )
);
CREATE INDEX [Type_idx] ON [mydb].[AFDX_TX_port] ([Type]);
CREATE INDEX [transmission_type_idx] ON [mydb].[AFDX_TX_port] ([transmission_type]);
CREATE INDEX [fk_AFDX_TX_port_EQUIPMENT1_idx] ON [mydb].[AFDX_TX_port] ([EQUIPMENT]);


CREATE TABLE [mydb].[AFDX_signal_FLOAT_caract](
 [id] INTEGER CONSTRAINT [pk_AFDX_signal_FLOAT_caract] PRIMARY KEY  NOT NULL,  
 [min] FLOAT NULL,  
 [max] FLOAT NULL,  
 [Unit_id] INTEGER NOT NULL,  
 [Coding_type_id] INTEGER NOT NULL,  
 [accuracy] FLOAT NULL,  
  CONSTRAINT [fk_AFDX_signal_FLOAT_caract_Unit1] 
  FOREIGN KEY([Unit_id])
    REFERENCES [Unit] ( [id] ),  
  CONSTRAINT [fk_AFDX_signal_FLOAT_caract_Float_Coding_type1] 
  FOREIGN KEY([Coding_type_id])
    REFERENCES [Coding_type] ( [id] )
);
CREATE INDEX [fk_AFDX_signal_FLOAT_caract_Unit1_idx] ON [mydb].[AFDX_signal_FLOAT_caract] ([Unit_id]);
CREATE INDEX [fk_AFDX_signal_FLOAT_caract_Float_Coding_type1_idx] ON [mydb].[AFDX_signal_FLOAT_caract] ([Coding_type_id]);


CREATE TABLE [mydb].[Ports_IN](
 [id] INTEGER CONSTRAINT [pk_Ports_IN] PRIMARY KEY  NOT NULL,  
 [Name] VARCHAR( 45 ) NOT NULL,  
 [Type] INTEGER NOT NULL,  
 [Unit] INTEGER NULL,  
 [Description] VARCHAR( 45 ) NULL,  
 [Convention] VARCHAR( 45 ) NULL,  
 [Dim1] INTEGER NOT NULL,  
 [Dim2] INTEGER NOT NULL,  
 [Com_Format] INTEGER NULL,  
 [Com_Mode] INTEGER NULL,  
 [From] VARCHAR( 45 ) NULL,  
 [Refresh] INTEGER NULL,  
 [Min] NUMERIC NULL,  
 [Max] NUMERIC NULL,  
 [Enum] VARCHAR( 45 ) NULL,  
 [Consummed_If] VARCHAR( 45 ) NULL,  
 [Aircraft_Signal_Name] VARCHAR( 45 ) NULL,  
 [Interface_Level] INTEGER NULL,  
 [Status] INTEGER NULL,  
 [Inits] NUMERIC NULL,  
 [Model] INTEGER NOT NULL,  
 [Micd] INTEGER NULL,  
  CONSTRAINT [Model] 
  FOREIGN KEY([Model])
    REFERENCES [Models] ( [id] ),  
  CONSTRAINT [Type] 
  FOREIGN KEY([Type])
    REFERENCES [Data_Type] ( [id] ),  
  CONSTRAINT [Unit] 
  FOREIGN KEY([Unit])
    REFERENCES [Unit] ( [id] ),  
  CONSTRAINT [Com_Format] 
  FOREIGN KEY([Com_Format])
    REFERENCES [Com_Format] ( [id] ),  
  CONSTRAINT [Com_Mode] 
  FOREIGN KEY([Com_Mode])
    REFERENCES [Com_Mode] ( [id] ),  
  CONSTRAINT [Interface_Level] 
  FOREIGN KEY([Interface_Level])
    REFERENCES [Interface_level] ( [id] ),  
  CONSTRAINT [Status] 
  FOREIGN KEY([Status])
    REFERENCES [status] ( [id] ),  
  CONSTRAINT [Micd] 
  FOREIGN KEY([Micd])
    REFERENCES [MICD] ( [id] )
    ON DELETE SET NULL
);
CREATE INDEX [Model_idx] ON [mydb].[Ports_IN] ([Model]);
CREATE INDEX [Type_idx] ON [mydb].[Ports_IN] ([Type]);
CREATE INDEX [Unit_idx] ON [mydb].[Ports_IN] ([Unit]);
CREATE INDEX [Com_Format_idx] ON [mydb].[Ports_IN] ([Com_Format]);
CREATE INDEX [Com_Mode_idx] ON [mydb].[Ports_IN] ([Com_Mode]);
CREATE INDEX [Interface_Level_idx] ON [mydb].[Ports_IN] ([Interface_Level]);
CREATE INDEX [Status_idx] ON [mydb].[Ports_IN] ([Status]);
CREATE INDEX [Micd_idx] ON [mydb].[Ports_IN] ([Micd]);


CREATE TABLE [mydb].[Ports_OUT](
 [id] INTEGER CONSTRAINT [pk_Ports_OUT] PRIMARY KEY  NOT NULL,  
 [Name] VARCHAR( 45 ) NOT NULL,  
 [Type] INTEGER NOT NULL,  
 [Unit] INTEGER NULL,  
 [Description] VARCHAR( 45 ) NULL,  
 [Convention] VARCHAR( 45 ) NULL,  
 [Dim1] INTEGER NOT NULL,  
 [Dim2] INTEGER NOT NULL,  
 [Com_Format] INTEGER NULL,  
 [Com_Mode] INTEGER NULL,  
 [To] VARCHAR( 45 ) NULL,  
 [Refresh] VARCHAR( 45 ) NULL,  
 [Min] NUMERIC NULL,  
 [Max] NUMERIC NULL,  
 [Enum] VARCHAR( 45 ) NULL,  
 [Produced_If] VARCHAR( 45 ) NULL,  
 [Aircraft_Signal_Name] VARCHAR( 45 ) NULL,  
 [Interface_Level] INTEGER NULL,  
 [Status] INTEGER NULL,  
 [Default_value] NUMERIC NULL,  
 [Micd] INTEGER NULL,  
 [Models_id] INTEGER NOT NULL,  
 [Models_Micd] INTEGER NOT NULL,  
  CONSTRAINT [Type] 
  FOREIGN KEY([Type])
    REFERENCES [Data_Type] ( [id] ),  
  CONSTRAINT [Unit] 
  FOREIGN KEY([Unit])
    REFERENCES [Unit] ( [id] ),  
  CONSTRAINT [Com_Format] 
  FOREIGN KEY([Com_Format])
    REFERENCES [Com_Format] ( [id] ),  
  CONSTRAINT [Com_Mode] 
  FOREIGN KEY([Com_Mode])
    REFERENCES [Com_Mode] ( [id] ),  
  CONSTRAINT [Interface_Level] 
  FOREIGN KEY([Interface_Level])
    REFERENCES [Interface_level] ( [id] ),  
  CONSTRAINT [Status] 
  FOREIGN KEY([Status])
    REFERENCES [status] ( [id] ),  
  CONSTRAINT [Micd] 
  FOREIGN KEY([Micd])
    REFERENCES [MICD] ( [id] )
    ON DELETE SET NULL,  
  CONSTRAINT [Models] 
  FOREIGN KEY([Models_id])
    REFERENCES [Models] ( [id] )
);
CREATE INDEX [Type_idx] ON [mydb].[Ports_OUT] ([Type]);
CREATE INDEX [Unit_idx] ON [mydb].[Ports_OUT] ([Unit]);
CREATE INDEX [Com_Format_idx] ON [mydb].[Ports_OUT] ([Com_Format]);
CREATE INDEX [Com_Mode_idx] ON [mydb].[Ports_OUT] ([Com_Mode]);
CREATE INDEX [Interface_Level_idx] ON [mydb].[Ports_OUT] ([Interface_Level]);
CREATE INDEX [Status_idx] ON [mydb].[Ports_OUT] ([Status]);
CREATE INDEX [Micd_idx] ON [mydb].[Ports_OUT] ([Micd]);
CREATE INDEX [Models_idx] ON [mydb].[Ports_OUT] ([Models_id]);


CREATE TABLE [mydb].[Connexions](
 [id] INTEGER CONSTRAINT [pk_Connexions] PRIMARY KEY  NOT NULL,  
 [Producer_model] INTEGER NULL,  
 [Producer_port] INTEGER NULL,  
 [Producer_operator] INTEGER NULL,  
 [Producer_tab] VARCHAR( 45 ) NULL,  
 [Signal] INTEGER NULL,  
 [Consummer_model] INTEGER NULL,  
 [Consummer_port] INTEGER NULL,  
 [Consummer_operator] INTEGER NULL,  
 [Consummer_tab] VARCHAR( 45 ) NULL,  
 [flot_id] INTEGER NULL,  
  CONSTRAINT [Producer_model] 
  FOREIGN KEY([Producer_model])
    REFERENCES [Models] ( [id] ),  
  CONSTRAINT [Producer_port] 
  FOREIGN KEY([Producer_port])
    REFERENCES [Ports_OUT] ( [id] ),  
  CONSTRAINT [Producer_opertor] 
  FOREIGN KEY([Producer_operator])
    REFERENCES [Operators] ( [id] ),  
  CONSTRAINT [Signal] 
  FOREIGN KEY([Signal])
    REFERENCES [Signals] ( [Id] ),  
  CONSTRAINT [Consummer_port] 
  FOREIGN KEY([Consummer_port])
    REFERENCES [Ports_IN] ( [id] ),  
  CONSTRAINT [Consummer_operator] 
  FOREIGN KEY([Consummer_operator])
    REFERENCES [Operators] ( [id] ),  
  CONSTRAINT [Consummer_model] 
  FOREIGN KEY([Consummer_model])
    REFERENCES [Models] ( [id] ),  
  CONSTRAINT [flot] 
  FOREIGN KEY([flot_id])
    REFERENCES [flot] ( [id] )
);
CREATE INDEX [Producer_model_idx] ON [mydb].[Connexions] ([Producer_model]);
CREATE INDEX [Consummer_model_idx] ON [mydb].[Connexions] ([Consummer_model]);
CREATE INDEX [Consummer_operator_idx] ON [mydb].[Connexions] ([Consummer_operator]);
CREATE INDEX [Consummer_port_idx] ON [mydb].[Connexions] ([Consummer_port]);
CREATE INDEX [Signal_idx] ON [mydb].[Connexions] ([Signal]);
CREATE INDEX [Producer_opertor_idx] ON [mydb].[Connexions] ([Producer_operator]);
CREATE INDEX [Producer_port_idx] ON [mydb].[Connexions] ([Producer_port]);
CREATE INDEX [flot_idx] ON [mydb].[Connexions] ([flot_id]);


CREATE TABLE [mydb].[AFDX_VL](
 [id] INTEGER CONSTRAINT [pk_AFDX_VL] PRIMARY KEY  NOT NULL,  
 [VL_name] VARCHAR( 45 ) NULL,  
 [VL_Identifier] INTEGER NULL,  
 [Network_sel] VARCHAR( 3 ) NULL,  
 [BAG] INTEGER NULL,  
 [MAX_frame_size] INTEGER NULL,  
 [Sub_VL_Number] INTEGER NULL,  
 [Sub_VL_Identifier] INTEGER NULL,  
 [AFDX_VLcol] VARCHAR( 45 ) NULL,  
 [TX_Equipment] INTEGER NOT NULL,  
 [TX_port] INTEGER NOT NULL,  
 [TX_Connector] INTEGER NOT NULL,  
 [IC_active] BIT NULL,  
 [Skew_max] INTEGER NULL,  
  CONSTRAINT [TX_Equipment] 
  FOREIGN KEY([TX_Equipment])
    REFERENCES [EQUIPMENT] ( [id] ),  
  CONSTRAINT [fk_AFDX_VL_AFDX_TX_port1] 
  FOREIGN KEY([TX_port])
    REFERENCES [AFDX_TX_port] ( [id] ),  
  CONSTRAINT [fk_AFDX_VL_CONNECTOR1] 
  FOREIGN KEY([TX_Connector])
    REFERENCES [CONNECTOR] ( [id] )
);
CREATE INDEX [TX_Equipment_idx] ON [mydb].[AFDX_VL] ([TX_Equipment]);
CREATE INDEX [fk_AFDX_VL_AFDX_TX_port1_idx] ON [mydb].[AFDX_VL] ([TX_port]);
CREATE INDEX [fk_AFDX_VL_CONNECTOR1_idx] ON [mydb].[AFDX_VL] ([TX_Connector]);


CREATE TABLE [mydb].[AFDX_MESSAGE](
 [id] INTEGER CONSTRAINT [pk_AFDX_MESSAGE] PRIMARY KEY  NOT NULL,  
 [AFDX_application_id] INTEGER NOT NULL,  
 [AFDX_VL_id] INTEGER NOT NULL,  
 [AFDX_TX_port_id] INTEGER NOT NULL,  
 [description] VARCHAR( 45 ) NULL,  
 [ref_doc] VARCHAR( 45 ) NULL,  
 [type] VARCHAR( 45 ) NULL,  
 [AFDX_Message_type_id] INTEGER NOT NULL,  
 [Protocol_type] VARCHAR( 45 ) NULL,  
 [Lenght] INTEGER NULL,  
 [Global_spare] INTEGER NULL,  
 [Transmission_rate] INTEGER NULL,  
 [Port_refresh_rate] INTEGER NULL,  
 [AFDX_MESSAGEcol] VARCHAR( 45 ) NULL,  
  CONSTRAINT [fk_AFDX_MESSAGE_AFDX_application1] 
  FOREIGN KEY([AFDX_application_id])
    REFERENCES [AFDX_application] ( [id] ),  
  CONSTRAINT [fk_AFDX_MESSAGE_AFDX_VL1] 
  FOREIGN KEY([AFDX_VL_id])
    REFERENCES [AFDX_VL] ( [id] ),  
  CONSTRAINT [fk_AFDX_MESSAGE_AFDX_TX_port1] 
  FOREIGN KEY([AFDX_TX_port_id])
    REFERENCES [AFDX_TX_port] ( [id] ),  
  CONSTRAINT [fk_AFDX_MESSAGE_AFDX_Message_type1] 
  FOREIGN KEY([AFDX_Message_type_id])
    REFERENCES [AFDX_Message_type] ( [id] )
);
CREATE INDEX [fk_AFDX_MESSAGE_AFDX_application1_idx] ON [mydb].[AFDX_MESSAGE] ([AFDX_application_id]);
CREATE INDEX [fk_AFDX_MESSAGE_AFDX_VL1_idx] ON [mydb].[AFDX_MESSAGE] ([AFDX_VL_id]);
CREATE INDEX [fk_AFDX_MESSAGE_AFDX_TX_port1_idx] ON [mydb].[AFDX_MESSAGE] ([AFDX_TX_port_id]);
CREATE INDEX [fk_AFDX_MESSAGE_AFDX_Message_type1_idx] ON [mydb].[AFDX_MESSAGE] ([AFDX_Message_type_id]);


CREATE TABLE [mydb].[AFDX_FDS](
 [id] INTEGER CONSTRAINT [pk_AFDX_FDS] PRIMARY KEY  NOT NULL,  
 [name] VARCHAR( 45 ) NULL,  
 [description] VARCHAR( 45 ) NULL,  
 [lenght] INTEGER NULL,  
 [spare_lenght] INTEGER NULL,  
 [adress_in_message] INTEGER NULL,  
 [AFDX_MESSAGE_id] INTEGER NOT NULL,  
 [AFDX_FS_id] INTEGER NOT NULL,  
  CONSTRAINT [fk_AFDX_FDS_AFDX_MESSAGE1] 
  FOREIGN KEY([AFDX_MESSAGE_id])
    REFERENCES [AFDX_MESSAGE] ( [id] ),  
  CONSTRAINT [fk_AFDX_FDS_AFDX_FS1] 
  FOREIGN KEY([AFDX_FS_id])
    REFERENCES [AFDX_FS] ( [id] )
);
CREATE INDEX [fk_AFDX_FDS_AFDX_MESSAGE1_idx] ON [mydb].[AFDX_FDS] ([AFDX_MESSAGE_id]);
CREATE INDEX [fk_AFDX_FDS_AFDX_FS1_idx] ON [mydb].[AFDX_FDS] ([AFDX_FS_id]);


CREATE TABLE [mydb].[AFDX_FS](
 [id] INTEGER CONSTRAINT [pk_AFDX_FS] PRIMARY KEY  NOT NULL,  
 [name] VARCHAR( 45 ) NULL,  
 [description] VARCHAR( 45 ) NULL,  
 [adress_in_message] INTEGER NULL,  
 [AFDX_MESSAGE_id] INTEGER NOT NULL,  
  CONSTRAINT [fk_AFDX_FS_AFDX_MESSAGE1] 
  FOREIGN KEY([AFDX_MESSAGE_id])
    REFERENCES [AFDX_MESSAGE] ( [id] )
);
CREATE INDEX [fk_AFDX_FS_AFDX_MESSAGE1_idx] ON [mydb].[AFDX_FS] ([AFDX_MESSAGE_id]);


CREATE TABLE [mydb].[AFDX_signal](
 [id] INTEGER CONSTRAINT [pk_AFDX_signal] PRIMARY KEY  NOT NULL,  
 [name] VARCHAR( 45 ) NULL,  
 [AFDX_signal_type_id] INTEGER NOT NULL,  
 [description] VARCHAR( 45 ) NULL,  
 [ref_doc] VARCHAR( 45 ) NULL,  
 [nb_of_bit] INTEGER NULL,  
 [adress] VARCHAR( 45 ) NULL,  
 [position] INTEGER NULL,  
 [AFDX_signal_BOOL_caract_id] INTEGER NULL,  
 [AFDX_signal_String_carac_id] INTEGER NULL,  
 [AFDX_Enumerate_caract_id] INTEGER NULL,  
 [AFDX_signal_FLOAT_caract_id] INTEGER NULL,  
 [AFDX_signal_INT_caract_id] INTEGER NULL,  
 [AFDX_signal_opaque_caract_id] INTEGER NULL,  
 [AFDX_MESSAGE_id] INTEGER NOT NULL,  
 [AFDX_FDS_id] INTEGER NOT NULL,  
 [AFDX_FS_id] INTEGER NOT NULL,  
  CONSTRAINT [fk_AFDX_signal_AFDX_signal_type1] 
  FOREIGN KEY([AFDX_signal_type_id])
    REFERENCES [AFDX_signal_type] ( [id] ),  
  CONSTRAINT [fk_AFDX_signal_AFDX_signal_BOOL_caract1] 
  FOREIGN KEY([AFDX_signal_BOOL_caract_id])
    REFERENCES [AFDX_signal_BOOL_caract] ( [id] ),  
  CONSTRAINT [fk_AFDX_signal_AFDX_signal_String_carac1] 
  FOREIGN KEY([AFDX_signal_String_carac_id])
    REFERENCES [AFDX_signal_String_caract] ( [id] ),  
  CONSTRAINT [fk_AFDX_signal_AFDX_Enumerate_caract1] 
  FOREIGN KEY([AFDX_Enumerate_caract_id])
    REFERENCES [AFDX_Enumerate_caract] ( [id] ),  
  CONSTRAINT [fk_AFDX_signal_AFDX_signal_INT_caract1] 
  FOREIGN KEY([AFDX_signal_INT_caract_id])
    REFERENCES [AFDX_signal_INT_caract] ( [id] ),  
  CONSTRAINT [fk_AFDX_signal_AFDX_signal_opaque_caract1] 
  FOREIGN KEY([AFDX_signal_opaque_caract_id])
    REFERENCES [AFDX_signal_opaque_caract] ( [id] ),  
  CONSTRAINT [fk_AFDX_signal_AFDX_signal_FLOAT_caract1] 
  FOREIGN KEY([AFDX_signal_FLOAT_caract_id])
    REFERENCES [AFDX_signal_FLOAT_caract] ( [id] ),  
  CONSTRAINT [fk_AFDX_signal_AFDX_MESSAGE1] 
  FOREIGN KEY([AFDX_MESSAGE_id])
    REFERENCES [AFDX_MESSAGE] ( [id] ),  
  CONSTRAINT [fk_AFDX_signal_AFDX_FDS1] 
  FOREIGN KEY([AFDX_FDS_id])
    REFERENCES [AFDX_FDS] ( [id] ),  
  CONSTRAINT [fk_AFDX_signal_AFDX_FS1] 
  FOREIGN KEY([AFDX_FS_id])
    REFERENCES [AFDX_FS] ( [id] )
);
CREATE INDEX [fk_AFDX_signal_AFDX_signal_type1_idx] ON [mydb].[AFDX_signal] ([AFDX_signal_type_id]);
CREATE INDEX [fk_AFDX_signal_AFDX_signal_BOOL_caract1_idx] ON [mydb].[AFDX_signal] ([AFDX_signal_BOOL_caract_id]);
CREATE INDEX [fk_AFDX_signal_AFDX_signal_String_carac1_idx] ON [mydb].[AFDX_signal] ([AFDX_signal_String_carac_id]);
CREATE INDEX [fk_AFDX_signal_AFDX_Enumerate_caract1_idx] ON [mydb].[AFDX_signal] ([AFDX_Enumerate_caract_id]);
CREATE INDEX [fk_AFDX_signal_AFDX_signal_INT_caract1_idx] ON [mydb].[AFDX_signal] ([AFDX_signal_INT_caract_id]);
CREATE INDEX [fk_AFDX_signal_AFDX_signal_opaque_caract1_idx] ON [mydb].[AFDX_signal] ([AFDX_signal_opaque_caract_id]);
CREATE INDEX [fk_AFDX_signal_AFDX_signal_FLOAT_caract1_idx] ON [mydb].[AFDX_signal] ([AFDX_signal_FLOAT_caract_id]);
CREATE INDEX [fk_AFDX_signal_AFDX_MESSAGE1_idx] ON [mydb].[AFDX_signal] ([AFDX_MESSAGE_id]);
CREATE INDEX [fk_AFDX_signal_AFDX_FDS1_idx] ON [mydb].[AFDX_signal] ([AFDX_FDS_id]);
CREATE INDEX [fk_AFDX_signal_AFDX_FS1_idx] ON [mydb].[AFDX_signal] ([AFDX_FS_id]);
