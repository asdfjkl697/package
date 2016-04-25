#include "obsolete.h"
#include <stdlib.h>
#include <string.h>

ObsoleteServer::ObsoleteServer(uint16_t port)
:_port(port), prve_packet(NULL)
{

}

ObsoleteServer::~ObsoleteServer(void)
{
	if(prve_packet !=NULL){
		free(prve_packet);
	}
	clients.clear();
}

void ObsoleteServer::OnTimer()
{
	_task->RemoveTimer(this);
	
    if(prve_packet != NULL){		 
	     uint8_t buffer[BUFFER_SIZE];
	     uint8_t *enc;
         Packet pkt(prve_packet->data, prve_packet->data_size);
		 enc = pkt.toHardware(buffer);
		 if(boardhandler!=NULL){
		     boardhandler->Send(buffer, enc - buffer);
	     }

		free(prve_packet);
		prve_packet = NULL;
	}
}

void ObsoleteServer::getFreq()
{
    uint8_t  buffer[64];

	Packet pkt(4);
	pkt.WriteByte(0x65);
	pkt.WriteByte(SYSTEM_SET);
	pkt.WriteByte(RF_Receiver); //module
	pkt.WriteByte(SYSTEM_READ);

	uint8_t *enc = pkt.toHardware(buffer);
	if(boardhandler!=NULL){
		boardhandler->Send(buffer, enc - buffer);
	}
}

void ObsoleteServer::Send(serial_packet *ser_pkt)
{
	Packet pkt(ser_pkt->data, ser_pkt->read_size);
	pkt.Skip(1);//Vserion
	
	uint8_t type = pkt.ReadByte();

	switch(type){
	    case CC1101:
			type = OLD_CC1101_433;
			break;
	    case CAN:
			type = OLD_CAN_Chip;
			break;
	    case RS485:
			type = OLD_RS485;
			break;
	    case SYSTEM_INFO:
			type = OLD_Module_Set;
			break;
		case SYSTEM_RETURN:
		{
			uint8_t module = pkt.ReadByte();			
			uint8_t act    = pkt.ReadByte();

			if(act == SYSTEM_READ || (act == SYSTEM_WIRTE)){
			   switch(module)
			   {
				  case RF_Receiver:
				  {
					 receiver_freq = pkt.ReadInt32();
					 break;
				  }
				  case RF_Transmit:
				  {
					 transmit_freq = pkt.ReadInt32();
					 break;
				  }
			   }
			}
			break;
			//return;
		}
	}

	if(type == RF_Receiver){
		uint8_t ready = 0;
		if(receiver_freq > 0){
			if(receiver_freq == 315000000){
				//type  = OLD_RXB8_315;
				type  = OLD_TX315_RAW;
				ready = 1;
			}
			if(receiver_freq == 433920000){
				//type  = OLD_RXB8_433;
				type  = OLD_TX433_RAW;
				ready = 1;
			}
		}
		
		if(!ready){
		   this->getFreq();
		   return;
		}
	}
		
	uint8_t temp[BUFFER_SIZE];
	uint8_t *enc = temp;
	//ser_pkt->data[1] = type;

	*enc++= ser_pkt->head;
	*enc++= ser_pkt->ack;
	*enc++= ser_pkt->data_size;
	memcpy(enc, ser_pkt->data, ser_pkt->data_size);
	enc+= ser_pkt->data_size;
	*enc++= ser_pkt->end_ack;

	temp[4] = type; //change type 
	
	std::list<Client *>::const_iterator it = clients.begin();
	for (; it != clients.end(); it++)
	{
		(*it)->Send(temp, enc - temp);
	}
}

void ObsoleteServer::OnAccept(Client *client)
{
	clients.push_back(client);
}

void ObsoleteServer::OnDisconnect(Client *client)
{
	clients.remove(client);
}


void ObsoleteServer::setfreq(uint8_t module, uint32_t freq)
{
    uint8_t  buffer[20];
	Packet pkt(8);
	pkt.WriteByte(0x65);
	pkt.WriteByte(SYSTEM_SET);
	pkt.WriteByte(module);
	pkt.WriteByte(SYSTEM_WIRTE);
	pkt.WriteInt32(freq);
	
	uint8_t *enc = pkt.toHardware(buffer);
	if(boardhandler!=NULL){
		boardhandler->Send(buffer, enc - buffer);
	}
}

void ObsoleteServer::transform(serial_packet *pkt)
{
	uint8_t type = pkt->data[1];
	uint32_t freq;

	switch(type)
	{
		case OLD_RXB8_315:
			pkt->data[1] = RF_Receiver;
			freq = 315000000;
			break;
	    case OLD_RXB8_433:
			pkt->data[1] = RF_Receiver;
			freq = 433920000;
			break;
		case OLD_TX315_RAW:
			pkt->data[1] = RF_Transmit;
			freq = 315000000;
			break;
	    case OLD_TX433_RAW:
			pkt->data[1] = RF_Transmit;
			freq = 433920000;
			break;
	    case OLD_CC1101_433:
			pkt->data[1] = CC1101;
			break;
	    case OLD_CAN_Chip:
			pkt->data[1] = CAN;
			break;
	    case OLD_RS485:
			pkt->data[1] = RS485;
			break;
	    case OLD_GSM:			
			return;
	    case OLD_Module_Set:
			pkt->data[1] = SYSTEM_INFO;
			break;
	    case SYSTEM_SET:
			break;
	    case 0x3a:
			break;
	    case 0x3b:
			break;
	    case 0x70: //jyc20160311 add
			break;
	    default:
			return;
    }

	if(pkt->data[1] == RF_Receiver){
	     setfreq(RF_Receiver, freq);
	}else if(pkt->data[1] == RF_Transmit && transmit_freq != freq){
	     setfreq(RF_Transmit, freq);

		 if(prve_packet == NULL){
		    prve_packet = (serial_packet *)malloc(sizeof(serial_packet));
		 }
		
		 memcpy(prve_packet, pkt, sizeof(serial_packet));
		
		 _task->AddTimer(this, 100);
	}else{
		uint8_t buffer[BUFFER_SIZE];
	    uint8_t *enc;
		Packet packet(pkt->data, pkt->data_size);
		enc = packet.toHardware(buffer);
		if(boardhandler!=NULL){
		   boardhandler->Send(buffer, enc - buffer);
	    }
	}
}

void ObsoleteServer::OnDataRead(Client *client, uint8_t *data, int size)
{		
	serial_packet *prve = client->GetPrvePkt();
	int index = 0;
    for(; index< size; index++){
	    if(prve->data_size == 0){
		   if(data[index] == 0xBC && data[index+1]==0xAC){  //double size chack
				 prve->head = data[index++];
				 prve->ack = data[index++];
				 prve->data_size = data[index];
		   }
	    }else if(prve->read_size < prve->data_size){
			  prve->data[prve->read_size++] = data[index];
		}else{
			  prve->end_ack = data[index];
			  if(prve->end_ack == prve->ack){
			/*printf("obssend %d\n",prve->read_size);
			uint16_t i;
			for(i=0;i<prve->read_size;i++)
				printf("%x ",prve->data[i]);
			printf("\n");*/
                  transform(prve);
			  }
			  prve->data_size = 0;
			  prve->read_size = 0;
		}
	}
}
