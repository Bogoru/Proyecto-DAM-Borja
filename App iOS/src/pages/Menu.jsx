import { IonContent, IonPage} from '@ionic/react';
import React, { useEffect } from 'react';
import { BleClient } from '@capacitor-community/bluetooth-le';
import { ReactSVG } from 'react-svg';
import { BLE } from '@ionic-native/ble';

import './Menu.css';
import Mover from '../imagenes/mover.svg'
import Lluvia from '../imagenes/lluvia.svg'
import Reloj from '../imagenes/reloj.svg'
import Volver from '../imagenes/volver.svg'

function Menu(){

    const HEART_RATE_SERVICE = '0000abcd-0000-1000-8000-00805f9b34fb';

    useEffect(() => {
        const interval = setInterval(() => {
    
          BLE.connectedPeripheralsWithServices([HEART_RATE_SERVICE]).then(
            async peripherals => {
              console.log('Dispositivos conectados con el servicio ' + HEART_RATE_SERVICE + ':');
              for(let i = 0; i < peripherals.length; i++) {
                console.log(peripherals[i].id);
              }
    
              if(peripherals.length <= 0){
                window.location.href ='/Dispositivos';
              }
    
            },
            error => {
              console.log('Error al buscar dispositivos conectados: ' + error);
            }
          );
    
        }, 1000);
    
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
    
            BLE.connectedPeripheralsWithServices([HEART_RATE_SERVICE]).then(
                async peripherals => {
                  console.log('Dispositivos conectados con el servicio ' + HEART_RATE_SERVICE + ':');
                  for(let i = 0; i < peripherals.length; i++) {
                    console.log(peripherals[i].id);
                    await BleClient.disconnect(peripherals[i].id);
                    window.location.href ='/Dispositivos';
                }
                },
                error => {
                  console.log('Error al buscar dispositivos conectados: ' + error);
                }
              );
          
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