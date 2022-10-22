<?php
    include_once('autoload.class.php');
    class Temperatura extends BancoDados{
        
        private $id;
        private $temp;
        private $acx;
        private $acy;
        private $gyx;
        private $gyy;
        
        public function __construct($id,$temp,$acx,$acy,$gyx,$gyy){
            $this->setId($id);
            $this->setTemp($temp);
            $this->setAcx($acx);
            $this->setAcy($acy);
            $this->setGyx($gyx);
            $this->setGyy($gyy);
        }

        public function setId($id){if($id > 0){$this->id = $id;}}
        public function getId(){return $this->id;}

        public function setTemp($temp){if($temp != ""){$this->temp = $temp;}}
        public function getTemp(){return $this->temp;}

        public function setAcx($acx){if($acx != ""){$this->acx = $acx;}}
        public function getAcx(){return $this->acx;}

        public function setAcy($acy){if($acy != ""){$this->acy = $acy;}}
        public function getAcy(){return $this->acy;}

        public function setGyx($gyx){if($gyx != ""){$this->gyx = $gyx;}}
        public function getGyx(){return $this->gyx;}

        public function setGyy($gyy){if($gyy != ""){$this->gyy = $gyy;}}
        public function getGyy(){return $this->gyy;}
        
        public function Salvar(){
            try{
                $sql = "INSERT INTO `ifc`.`temp_table` (`temp_value`, `AcY`, `AcX` , `GyX`, `GyY`) 
                        VALUES (:temp, :acy, :acx, :gyx, :gyy)";
                $param = array( ":temp" => $this->getTemp(),
                                ":acy" => $this->getAcy(),
                                ":acx" => $this->getAcx(),
                                ":gyx" => $this->getGyx(),
                                ":gyy" => $this->getGyy());
                $teste = parent::Execute($sql,$param);
                return $teste;
            }catch(Exception $e){
                echo "Erro ao salvar: ('{$e->getMessage()}')\n{$e}\n";
            }
        }

        public function __toString(){
            return "ID: ".$this->getId() ."<br>
                    Temperatura: ".$this->getTemp() ."<br>
                    Aceleração eixo X: ".$this->getAcx() ."<br>
                    Aceleração eixo Y: ".$this->getAcy();;    
        }
    }
?>