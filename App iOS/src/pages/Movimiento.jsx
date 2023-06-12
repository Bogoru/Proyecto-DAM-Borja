import { IonContent, IonHeader, IonPage, IonToolbar} from '@ionic/react';
import { useEffect } from 'react';
import { BleClient, numbersToDataView } from '@capacitor-community/bluetooth-le';
import './Movimiento.css';
import { ReactSVG } from 'react-svg';

import { BLE } from '@ionic-native/ble';
import headerControl from '../imagenes/headercontrol.svg'
import abrirTodo from '../imagenes/abrirtodo.svg'
import cerrarTodo from '../imagenes/cerrartodo.svg'
import abrir1 from '../imagenes/abrir.svg'
import cerrar1 from '../imagenes/cerrar.svg'
import barra from '../imagenes/barra.svg'
import Volver from '../imagenes/volver.svg'

function Home () {

  const HEART_RATE_SERVICE = '0000abcd-0000-1000-8000-00805f9b34fb';
  const WRITE_CHARACTERISTIC = "00001234-0000-1000-8000-00805F9B34FB";

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

  async function abrir(){

    try {

        if(BleClient.getConnectedDevices([]) === 0){
        
          window.location.href ='/Dispositivos';
    
        }else{
    
          BLE.connectedPeripheralsWithServices([HEART_RATE_SERVICE]).then(
            async peripherals => {
              console.log('Dispositivos conectados con el servicio ' + HEART_RATE_SERVICE + ':');
              for(let i = 0; i < peripherals.length; i++) {
                console.log(peripherals[i].id);
                await BleClient.write(peripherals[i].id, HEART_RATE_SERVICE, WRITE_CHARACTERISTIC, numbersToDataView([1]));
              }
            },
            error => {
              console.log('Error al buscar dispositivos conectados: ' + error);
            }
          );
  
        }
  
      } catch (error) {
        console.error(error);
      }

  }

  async function cerrar(){

    try {

        if(BleClient.getConnectedDevices([]) === 0){
        
          window.location.href ='/Dispositivos';
    
        }else{
    
          BLE.connectedPeripheralsWithServices([HEART_RATE_SERVICE]).then(
            async peripherals => {
              console.log('Dispositivos conectados con el servicio ' + HEART_RATE_SERVICE + ':');
              for(let i = 0; i < peripherals.length; i++) {
                console.log(peripherals[i].id);
                await BleClient.write(peripherals[i].id, HEART_RATE_SERVICE, WRITE_CHARACTERISTIC, numbersToDataView([2]));
              }
            },
            error => {
              console.log('Error al buscar dispositivos conectados: ' + error);
            }
          );
  
        }
  
      } catch (error) {
        console.error(error);
      }

  }

  async function parar(){

    try {

        if(BleClient.getConnectedDevices([]) === 0){
        
          window.location.href ='/Dispositivos';
    
        }else{
    
          BLE.connectedPeripheralsWithServices([HEART_RATE_SERVICE]).then(
            async peripherals => {
              console.log('Dispositivos conectados con el servicio ' + HEART_RATE_SERVICE + ':');
              for(let i = 0; i < peripherals.length; i++) {
                console.log(peripherals[i].id);
                await BleClient.write(peripherals[i].id, HEART_RATE_SERVICE, WRITE_CHARACTERISTIC, numbersToDataView([3]));
              }
            },
            error => {
              console.log('Error al buscar dispositivos conectados: ' + error);
            }
          );
  
        }
  
      } catch (error) {
        console.error(error);
      }

  }

  function back(){
    window.location.href ='/Menu';
  }

  return (
    <IonPage>
      <IonHeader className='fondo2'>
        <IonToolbar className='fondo2'>
            <ReactSVG src={headerControl} className='svg'></ReactSVG>
        </IonToolbar>
      </IonHeader>
      <IonContent fullscreen className='fondo2' scrollY="false">

            <ReactSVG src={abrirTodo} onClick={abrir} className='svg1'></ReactSVG>
            <ReactSVG src={cerrarTodo} onClick={cerrar} className='svg1'></ReactSVG>

            <ReactSVG src={barra} className='svg1'></ReactSVG>

            <ReactSVG src={abrir1} onPointerDown={abrir} onPointerUp={parar} className='svg1'></ReactSVG>
            <ReactSVG src={cerrar1} onPointerDown={cerrar} onPointerUp={parar} className='svg1'></ReactSVG>

            <ReactSVG src={barra} className='svg1'></ReactSVG>

            <ReactSVG src={Volver} className='imgAtras' onClick={back}></ReactSVG>

      </IonContent>
    </IonPage>
  );

};

export default Home;
