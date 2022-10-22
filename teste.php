<?php
   require_once('classe/autoload.class.php');
   $temperature = isset($_GET['temperature']) ? $_GET['temperature'] : "";
   $acx = isset($_GET['acx']) ? $_GET['acx'] : "";
   $acy = isset($_GET['acy']) ? $_GET['acy'] : "";
   $gyx = isset($_GET['gyx']) ? $_GET['gyx'] : "";
   $gyy = isset($_GET['gyy']) ? $_GET['gyy'] : "";

   if(isset($temperature) && isset($acx) && isset($acy) && isset($gyx) && isset($gyy)){
         $temperatura = new Temperatura(0,$temperature,$acx,$acy,$gyx,$gyy);
         $temperatura->Salvar();
      }
?>