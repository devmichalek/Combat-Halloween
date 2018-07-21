<?php
  session_start();

  if(!isset($_SESSION['logged']))
  {
    header('Location: http://combathalloween.netne.net/user/loginform.php');
    exit();
  }

  require_once "../connect.php";
  mysqli_report(MYSQLI_REPORT_STRICT);
  $connection = @new mysqli($host, $db_user, $db_password, $db_name);

  if($result = @$connection->query( sprintf("SELECT * FROM users WHERE username='%s'", mysqli_real_escape_string($connection, $_SESSION['username']))))
  {
    $row = $result->fetch_assoc();
    
    if($row['permissions'] != "admin" && $row['permissions'] != "moderator")
    {
      $result->free_result();
      $connection->close();
      header('Location: http://combathalloween.netne.net/home.php');
      exit();
    }

    $result->free_result();
  }
  else
  {
    $result->free_result();
    $connection->close();
    header('Location: http://combathalloween.netne.net/home.php');
    exit();
  }


  if($connection->connect_errno == 0)
  {
    $IDname = $_GET['IDname'];
    
    $sql = "SELECT * FROM bugs WHERE IDname='$IDname'";
    $records = $connection->query($sql);
    $row=$records->fetch_assoc();
    
    $name = $row['name'];
    $type = $row['type'];
    $actiontodo = $row['action'];

    $description = $row['description'];
    $breaks = array("<br />","<br>","<br/>");  
      $description = str_ireplace($breaks, "", $description); 
    
    $location = $row['location'];
    $severity = $row['severity'];
    $priority = $row['priority'];
    $deadline = $row['deadline'];
    $author = $row['author'];
    $developer = $row['developer'];
    $resolution = $row['resolution'];
  }
  else
  {
    die("Could not connect: ".mysql_error());
  }
?>
    

<?php require_once("../head.php"); ?>

  <nav><div class="nav-wrapper">
      <div class="row">
          <a class="nav-main brand-logo">&nbsp;&nbsp;&nbsp;Combat&nbsp;Halloween</a>
          <a href="#" data-target="mobile-demo" class="sidenav-trigger"><i class="material-icons">menu</i></a>
          <ul id="nav-mobile" class="right hide-on-med-and-down">
              <li><a class="btn-floating btn-medium pulse blue lighten-1" href="../home.php"><i class="material-icons">home</i></a></li>
            <li><a class="nav btn red lighten-1 nav-button" href="index.php">Back</a></li>
          </ul>
        </div>
  </div></nav>
  <ul class="nav-main sidenav" id="mobile-demo">
      <li><a class="btn-floating btn-medium pulse blue lighten-1" href="../home.php"><i class="material-icons">home</i></a></li>
      <li><a class="nav btn red lighten-1 nav-button" href="index.php">Back</a></li>
  </ul>


  <div class="container center">
    
    <!-- Header -->
    <div class="s12"><h2>Combat Halloween Edit Bug</h2></div>
    
    <form class="col s6 push-s3" method="post" action="edit.php" style="margin-bottom: 20px;">
        
      <!-- HIDDEN ID NAME-->
        <input type="hidden" name="IDname" value="<?php echo $IDname; ?>" />
        
      <!-- NAME -->
      <div class="row">
      <div class="input-field col s12 m6 push-m3">
        <input id="name" type="text" class="validate" name="name" value="<?php echo $name; ?>">
        <label for="name"><h5 class="modcon2">Name</h5></label>
      </div>
      </div>

      <!-- TYPE, ACTION -->
      <div class="row">
        <div class="input-field col s6 m3 push-m3">
          <select name="type">
              <?php
                echo "<option "; if($type=="Bug")           echo " selected "; echo 'value="Bug">Bug</option>';
                echo "<option "; if($type=="Change")        echo " selected "; echo 'value="Change">Change</option>';
                echo "<option "; if($type=="New Feature")   echo " selected "; echo 'value="New Feature">New Feature</option>';
                echo "<option "; if($type=="Syntax Error")  echo " selected "; echo 'value="Syntax Error">Syntax Error</option>';
                echo "<option "; if($type=="Other")         echo " selected "; echo 'value="Other">Other</option>';
              ?>
          </select>
          <label>Type</label>
          </div>
        <div class="input-field col s6 m3 push-m3">
          <select name="actiontodo">
              <?php
                echo "<option "; if($actiontodo=="Repair")  echo " selected "; echo 'value="Repair">Repair</option>';
                echo "<option "; if($actiontodo=="Add")     echo " selected "; echo 'value="Add">Add</option>';
                echo "<option "; if($actiontodo=="Create")  echo " selected "; echo 'value="Create">Create</option>';
                echo "<option "; if($actiontodo=="Modify")  echo " selected "; echo 'value="Modify">Modify</option>';
                echo "<option "; if($actiontodo=="Correct") echo " selected "; echo 'value="Correct">Correct</option>';
                echo "<option "; if($actiontodo=="Remove")  echo " selected "; echo 'value="Remove">Remove</option>';
              ?>
          </select>
            <label>Action to do</label>
          </div>
        </div>
        
        <!-- DESCRIPTION -->
        <div class="row"><div class="input-field col s12 m6 push-m3">
          <textarea class="materialize-textarea" name="description"><?php echo $description; ?></textarea>
          <label>Description</label>
        </div></div>

        <!-- LOCATION OF THE BUG -->
        <div class="row"><div class="input-field col s12 m6 push-m3">
          <input id="location" type="text" class="validate" name="location" value="<?php echo $location; ?>">
          <label for="location"><h5 class="modcon2">Location</h5></label>
        </div></div>
          
          <!-- SEVERITY, PRIORITY -->
        <div class="row">
        <div class="input-field col s6 m3 push-m3">
          <select name="severity">
            <?php
              echo "<option "; if($severity=="Fatal") echo " selected "; echo 'value="Fatal">Fatal</option>';
              echo "<option "; if($severity=="Serious") echo " selected "; echo 'value="Serious">Serious</option>';
              echo "<option "; if($severity=="Minor") echo " selected "; echo 'value="Minor">Minor</option>';
            ?>
          </select>
          <label>Severity</label>
        </div>
        <div class="input-field col s6 m3 push-m3">
          <select name="priority">
            <?php
              echo "<option "; if($priority=="Must Do") echo " selected "; echo 'value="Must Do">Must Do</option>';
              echo "<option "; if($priority=="Low") echo " selected "; echo 'value="Low">Low</option>';
              echo "<option "; if($priority=="Normal")  echo " selected "; echo 'value="Normal">Normal</option>';
              echo "<option "; if($priority=="High")  echo " selected "; echo 'value="High">High</option>';
            ?>
          </select>
          <label>Priority</label>
        </div>
        </div>
            
          <!-- DEADLINE -->
        <div class="row">
          <div class="input-field col s12 m6 push-m3">
            <input id="deadline" type="text" class="datepicker" name="deadline" value="<?php echo $deadline; ?>">
            <label for="deadline"><h5 class="modcon2">Deadline</h5></label>
          </div>
        </div>

          <!-- AUTHOR -->
        <div class="row">
          <div class="disabled input-field col s12 m6 push-m3">
            <input id="author" type="text" class="validate" name="author" value="<?php echo $author;?>">
            <label for="author"><h5 class="modcon2">Author</h5></label>
          </div>
        </div>

          <!-- RESOLUTION, DEVELOPER -->
        <div class="row">
        <div class="input-field col s6 m3 push-m3">
          <select name="resolution">
            <?php
              echo "<option "; if($resolution=="Deferred")  echo " selected "; echo 'value="Deferred">Deferred</option>';
              echo "<option "; if($resolution=="Disagree")  echo " selected "; echo 'value="Disagree">Disagree</option>';
              echo "<option "; if($resolution=="Duplicated")  echo " selected "; echo 'value="Duplicated">Duplicated</option>';
              echo "<option "; if($resolution=="Fixed") echo " selected "; echo 'value="Fixed">Fixed</option>';
              echo "<option "; if($resolution=="Hold")  echo " selected "; echo 'value="Hold">Hold</option>';
              echo "<option "; if($resolution=="Implemented") echo " selected "; echo 'value="Implemented">Implemented</option>';
              echo "<option "; if($resolution=="In Development")  echo " selected "; echo 'value="In Development">In Development</option>';
              echo "<option "; if($resolution=="Irreproducible")  echo " selected "; echo 'value="Irreproducible">Irreproducible</option>';
              echo "<option "; if($resolution=="Known Problem") echo " selected "; echo 'value="Known Problem">Known Problem</option>';
              echo "<option "; if($resolution=="Need More Info")  echo " selected "; echo 'value="Need More Info">Need More Info</option>';
              echo "<option "; if($resolution=="New") echo " selected "; echo 'value="New">New</option>';
              echo "<option "; if($resolution=="Obsolete")  echo " selected "; echo 'value="Obsolete">Obsolete</option>';
              echo "<option "; if($resolution=="Reeopen") echo " selected "; echo 'value="Reeopen">Reeopen</option>';
              echo "<option "; if($resolution=="Revised") echo " selected "; echo 'value="Revised">Revised</option>';
              echo "<option "; if($resolution=="Not To Correct") echo " selected "; echo 'value="Not To Correct">Not To Correct</option>';
              echo "<option "; if($resolution=="Support Needed") echo " selected "; echo 'value="Support Needed">Support Needed</option>';
              echo "<option "; if($resolution=="Withdrawn") echo " selected "; echo 'value="Withdrawn">Withdrawn</option>';
            ?>
          </select>
          <label>Resolution</label>
        </div>
        <div class="input-field col s6 m3 push-m3">
          <select name="developer">
            <?php
              echo "<option "; if($developer=="devmichalek@gmail.com")  echo " selected "; echo 'value="devmichalek@gmail.com">devmichalek@gmail.com</option>';
              echo "<option "; if($developer=="sebastek321@gmail.com")  echo " selected "; echo 'value="sebastek321@gmail.com">sebastek321@gmail.com</option>';
              echo "<option "; if($developer=="kamilgawlik@icloud.com") echo " selected "; echo 'value="kamilgawlik@icloud.com">kamilgawlik@icloud.com</option>';
            ?>
          </select>
          <label>Choose developer</label>
        </div>
        </div>
        
        <div class="row">
        <!-- CANCEL BUTTON -->
        <a href="http://combathalloween.netne.net/bugs" class="waves-effect waves-light btn red lighten-1"><i class="material-icons right">clear</i>Cancel </a>
        
        <!-- DELETE BUTTON -->
        <a href="#bugdeleter" class="waves-effect waves-light btn modal-trigger purple lighten-1"><i class="material-icons right">delete</i>Delete </a>
        
        <!-- UPDATE BUTTON-->
        <button class="btn waves-effect waves-light green lighten-1 nav-button" type="submit" name="action">Update
          <i class="material-icons right">send</i>
        </button>
        </div>
        
    </form>
    
    <div id="bugdeleter" class="modal">
        <div class="modal-content">
            <h4 class="modcon">Information</h4>
            <h5>You want to delete bug "<?php echo $name; ?>" ID(<?php echo $IDname; ?>). Please confirm your decision.</h5>
        </div>
        <div class="modal-footer">
            <a class="modal-close waves-effect waves-blue btn-flat japokki"><i class='material-icons right'>clear</i>CANCEL </a>
            <form action="delete.php" method="get">
                <input type="hidden" name="IDname" value="<?php echo $IDname; ?>">
                <button type='submit' name="action" class="modal-close waves-effect waves-red btn-flat japokki"><i class='material-icons right'>delete</i>DELETE </button>
            </form>
        </div>
    </div>
    
  </div>

<?php require_once("../footer.php"); ?>