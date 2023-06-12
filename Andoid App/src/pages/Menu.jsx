import { IonContent, IonPage} from '@ionic/react';
import React, { useEffect } from 'react';
import { BleClient } from '@capacitor-community/bluetooth-le';
import { ReactSVG } from 'react-svg';

import './Menu.css';
import Mover from '../imagenes/mover.svg'
import Lluvia from '../imagenes/lluvia.svg'
import Reloj from '../imagenes/reloj.svg'
import Volver from '../imagenes/volver.svg'

function Menu(){

    useEffect(() => {
        const interval = setInterval(async () => {
    
          const devices = await BleClient.getConnectedDevices([]);
          console.log('Dispositivos conectados:', devices);
    
          if(devices == 0){
            window.location.href ='/Dispositivos';
          }
    
        }, 3000);
    
      }, []);

    function irMovimiento(){
        window.location.href ='/Movimiento';
    }

    function irLluvia(){
        window.location.href ='/Lluvia';
    }

    function irReloj(){
        window.location.href ='/Temporizador';
    }

    async function desconectar() {
        try {
    
          if(BleClient.getConnectedDevices([]) === 0){
            window.location.href ='/Dispositivos';
          }else{
            try {
              const devices = await BleClient.getConnectedDevices([]);
              console.log('Dispositivos conectados:', devices);
              
              devices.forEach(async (device) => {
                await BleClient.disconnect(device.deviceId);
              });
        
              window.location.href ='/Dispositivos';
              
            } catch (error) {
              console.error('Error al desconectar dispositivos:', error);
            }
          }
          
        } catch (error) {
          console.error('Error al desconectar dispositivos:', error);
          window.location.href ='/Home';
    
        }
      }
    
    return(
        <IonPage>
            <IonContent fullscreen className='contenido'>

                <div className='contenedor-imagenes2'> 
                    <ReactSVG src={Mover} className='img' onClick={irMovimiento}></ReactSVG>
                    <ReactSVG src={Reloj} className='img' onClick={irReloj}></ReactSVG>
                    <ReactSVG src={Lluvia} className='img' onClick={irLluvia}></ReactSVG>
                </div>   

                <ReactSVG src={Volver} className='img2' onClick={desconectar}></ReactSVG>

            </IonContent>
        </IonPage>

    );
}

export default Menu;