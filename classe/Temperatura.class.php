<?php
    include_once('autoload.class.php');
    class Temperatura extends BancoDados{
        
        private $id;
        private $temp;
        
        public function __construct($id,$temp){
            $this->setId($id);
            $this->setTemp($temp);
        }

        public function setId($id){if($id > 0){$this->id = $id;}}
        public function getId(){return $this->id;}

        public function setTemp($temp){if($temp != ""){$this->temp = $temp;}}
        public function getTemp(){return $this->temp;}
        
        public function Salvar(){
            try{
                $sql = "INSERT INTO `ifc`.`temp_table` (`temp_value`) VALUES (:temp)";
                $param = array( ":temp" => $this->getTemp());
                $teste = parent::Execute($sql,$param);
                return $teste;
            }catch(Exception $e){
                echo "Erro ao salvar: ('{$e->getMessage()}')\n{$e}\n";
            }
        }

        public function __toString(){
            return "ID: ".$this->getId()."<br>
                    Temperatura: ".$this->getTemp();    
        }
    }
?>