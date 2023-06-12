import { IonContent, IonHeader, IonPage, IonInput, IonToolbar, IonIcon, IonList, IonItem, IonFooter, IonButton, IonLabel } from '@ionic/react';
import { createOutline } from 'ionicons/icons';
import React, { useEffect, useState } from 'react';
import { BleClient, ScanMode } from '@capacitor-community/bluetooth-le';
import { ReactSVG } from 'react-svg';

import './Home.css';

import titulobuscar from '../imagenes/titulobuscar.svg'
import toldo from '../imagenes/toldo.svg'
import footer from '../imagenes/footer.svg'
import buscar from '../imagenes/buscar.svg'

const HEART_RATE_SERVICE = '0000abcd-0000-1000-8000-00805f9b34fb';

function Sillones(){

  const [scanning, setScanning] = useState(false);
  const [scanResults, setScanResults] = useState([]);

  const [showImage, setShowImage] = useState(false);
  const [connectedDeviceId, setConnectedDeviceId] = useState(null);
  const [deviceName, setDeviceName] = useState(null);

  const [showImage1, setShowImage1] = useState(true);
  const [showImage2, setShowImage2] = useState(true);
  const [inputValue, setInputValue] = useState(null);
  const [id1, setId1] = useState(null);

  const [toldos, setToldos] = useState(null);

  useEffect(() => {
    BleClient.initialize();
    setToldos(false);
  }, []);


  const guardar = (event) => {
    
    setInputValue(event.target.value);

    if(inputValue == null){

      ocultar2();

    }

  }

  const handleButtonClick = () => {

    localStorage.setItem(id1, inputValue);
    setDeviceName(inputValue);
    ocultar();
    ocultar2();
    setInputValue(null);
    
  };

  function buscarNombre(id){

    setDeviceName(localStorage.getItem(id));
    console.log('ESTE ES EL NOMBRE DEL DEVICE: ', deviceName);
    console.log('Este es el id', id);
    setId1(id);

  }

  function ocultar2(){
    setShowImage2(!showImage2);
  }

  function ocultar(){
    setShowImage1(!showImage1);
  }

  async function doScan(callback) {
    const device = await BleClient.requestLEScan({
      services: [HEART_RATE_SERVICE],
      scanMode: ScanMode.SCAN_MODE_LOW_LATENCY,
    }, callback);
  }

  function startScan() {
    setToldos(true);
    setScanResults([]);
    setScanning(true);
    doScan(result => setScanResults(scanResults => [...scanResults, result]))
      .finally(() => setScanning(false));
  }

  async function connectToDevice(deviceId) {
    try {

      await BleClient.connect(deviceId, (deviceId) => onDisconnect(deviceId));
      setConnectedDeviceId(deviceId);

      if(BleClient.isEnabled){
        BleClient.stopLEScan();
        window.location.href = '/Menu';
      }

    } catch (error) {
      console.error(error);
      recargar();
    }
  }

  async function onDisconnect(deviceId) {
    
    console.log(`Device disconnected: ${deviceId}`);
    setConnectedDeviceId(null);
    setScanResults(scanResults => {
      const filteredResults = scanResults.filter(r => r.device.deviceId !== deviceId);
      return filteredResults;
    });


  }

  function Mostrar(){

    if(scanResults == 0){

      if(toldos == false){
        setShowImage(false);
        return(
  
          <IonContent fullscreen className='fondo'>
            
            <ReactSVG src={buscar} className='svgBuscar' onClick={startScan}></ReactSVG>
  
            <ReactSVG src={toldo} className='svgToldo'></ReactSVG>
  
          </IonContent>
          )
      }else if(toldos == true){
        setShowImage(false);
        return(
  
          <IonContent fullscreen className='fondo'>
            
            <ReactSVG src={buscar} className='svgBuscar' onClick={startScan}></ReactSVG>
  
            <h2 className='textoNinguno'>Ningún Dispositivo Disponible</h2>

            <ReactSVG src={toldo} className='svgToldo'></ReactSVG>
  
          </IonContent>
          )
      }
    
    }else{
      setShowImage(true);
      setToldos(false);
      return(
        <IonContent fullscreen className='fondo'>

          <IonList className='Lista' lines="none">
              {scanResults.map((result) => (
                <IonItem className='Item' key={result.device.deviceId}>
                  {buscarNombre(result.device.deviceId)}
                  <button className='ButtonDispositivos' onClick={() => connectToDevice(result.device.deviceId)}>{deviceName ?? result.device.name}</button>
                  <IonIcon icon={createOutline} onClick={ocultar}></IonIcon>
                </IonItem>
                
              ))}

              {!showImage1 &&  <IonInput label='Nuevo Nombre: ' type="text" value={inputValue} onIonChange={guardar} className='input'/>}
              {!showImage2 && <IonButton onClick={handleButtonClick} className='buttonGuardar'>Guardar</IonButton>}

          </IonList>

        </IonContent>
      )
    }
  }

  function recargar(){
    window.location.reload();
  }

  return (
    <IonPage>
      <IonHeader className='fondo'>
        <IonToolbar  className='fondo'>
          <ReactSVG src={titulobuscar} className='svg'></ReactSVG>
        </IonToolbar>
      </IonHeader>

      <Mostrar/>

      <IonFooter>
          <ReactSVG src={footer} className='svg'></ReactSVG>
      </IonFooter>

    </IonPage>
  );
  
};

export default Sillones;
