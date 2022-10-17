<?php
require_once('classe/autoload.class.php');
$temperature = isset($_GET['temperature']) ? $_GET['temperature'] : "";
if(isset($temperature)) {
      $temperatura = new Temperatura(0,$temperature);
      $temperatura->Salvar();
      echo $temperatura;
   }
?>