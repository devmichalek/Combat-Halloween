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
    $sql = "SELECT * FROM bugs";
    $records = $connection->query($sql);

    $donenum = 0;
    $opennum = 0;
    $sumnum = 0;
    while($row=$records->fetch_assoc())
    {
      ++$sumnum;
      if($row['resolution'] == "Fixed" ||
         $row['resolution'] == "Implemented" ||
         $row['resolution'] == "Revised")
        ++$donenum;
      else
        ++$opennum;
    }
    mysqli_data_seek($records, 0);
  }
  else
  {
    die("Could not connect: ".mysql_error());
  }
?>
    

<?php require_once("../head.php"); ?>

  <div class="navbar-fixed"><nav><div class="nav-wrapper">
      <div class="row">
          <a class="nav-main brand-logo">&nbsp;&nbsp;&nbsp;Combat&nbsp;Halloween</a>
          <a href="#" data-target="mobile-demo" class="sidenav-trigger"><i class="material-icons">menu</i></a>
          <ul id="nav-mobile" class="right hide-on-med-and-down">
            <li><a class="nav" href="../home.php">Home</a></li>
            <li><a class="nav btn red lighten-1 nav-button" href="addbug.php">Add</a></li>
          </ul>
        </div>
  </div></nav></div>
    <ul class="nav-main sidenav" id="mobile-demo">
      <li><a class="nav" href="../home.php">Home</a></li>
      <li><a class="nav btn red lighten-1 nav-button" href="addbug.php">Add</a></li>
  </ul>

  <div class="container center">

    <div class="row">
      <h2 class="center">Combat Halloween Bugs</h2>
      <h4 class="modcon">The list of things to repair, modify, add, create or remove is below. What we called bug is a thing that need to be repair, It is usually memory leak or GUI errors. New feature is like: it would be nice to add this feature to the GUI, It is not necessary but rather sth that would ease users to interact with game or would make more fun while playing, so new files (png, wav etc.), new options inside GUI etc. Syntax Error, this type informs about language mistakes, It can be also a proposal to rename sth. If the info button is red that means it is your task.</h4>
      <h4 class="modcon">Done: <?php echo $donenum;?> Open: <?php echo $opennum;?> All: <?php echo $sumnum;?></h4>
      <div class="center col s12">
        <table class="striped centered responsive-table bordered">
              <thead class="tableheader">
                <tr>
                    <th>Name</th>
                    <th>Type</th>
                    <th>Description</th>
                    <th>Location</th>
                    <th>Severity</th>
                    <th>Priority</th>
                    <th>Deadline</th>
                    <th>Resolution</th>
                </tr>
              </thead>
          <tbody class="member">
          
          <?php

            while($row=$records->fetch_assoc())
            {
              echo "<tr>";
              
              // Color
              $color = "''";
              $resolution = $row['resolution'];
              if($resolution == "Fixed" ||
                 $resolution == "Revised" ||
                 $resolution == "Implemented")
              $color = "'grey lighten-2'";

              // Name
              echo "<td class=".$color.">";
              echo '<form action="editbug.php" method="get">';
              echo $row['name'];
              echo '<input type="hidden" name="name" value="';
              echo $row['name'].'"> ';
              $descolor = ltrim($color, "'");
              if($descolor == "")
                  $descolor = "amber lighten-1'";
              echo "<button type='submit' class='btn ".$descolor.">Edit</button>";
              echo '</form>'."</td>";

              // Type
              $type = $row['type'];
              if($color == "''")
              {
                  switch($type)
                  {
                      case "Bug":             echo "<td class='red lighten-1'>".$type."</td>";   break;
                      case "Change":          echo "<td class='amber lighten-1'>".$type."</td>"; break;
                      case "New Feature":     echo "<td class='green lighten-1'>".$type."</td>"; break;
                      case "Syntax Error":    echo "<td class='red lighten-1'>".$type."</td>";   break;
                      default:                echo "<td class='grey lighten-1'>".$type."</td>";  break;
                  }
              }
              else
                  echo "<td class=".$color.">".$type."</td>";

              // Description (button + form)
              echo "<td class=".$color.">";
              $descolor = ltrim($color, "'");
              
              if($descolor == "")
              {
                  $descolor = "'";
                  if($row['developer'] == $_SESSION['email'])
                      $descolor = "red lighten-1'";
                  
              }
              
              echo "<a class='waves-effect waves-light btn modal-trigger ".$descolor." ";
              echo "href='#".$row['name']."'>";
              echo "Info</a></td>";
              echo "<div id='".$row['name']."' class='modal'>";
                echo "<div class='modal-content'>";
                echo "<h4 class='modcon'>".$row['name']."</h4>";
                echo "<p class='japokki red lighten-1'>Reported by: ".$row['author']."</p>";
                echo "<p class='japokki blue'>Developer: ".$row['developer'];"</p>";
                echo "<p class='japokki'>Action to do: ".$row['action']."</p>";
                echo "<p class='japokki'>".$row['description']."</p>";
                echo "</div>";
                echo '<div class="modal-footer">';
                echo '<a href="#!" class="modal-close waves-effect waves-green btn-flat japokki">Ok</a>';
                echo "</div>";
                echo "</div>";

                // Location - link
                $location = $row['location'];
                echo "<td class=".$color.">";
                if($location == "None")
                  echo "None</td>";
                else
                    echo "<a target='_blank' href='".$location."'>Link</a></td>";
              
              // Severity
              $severity = $row['severity'];
              if($color == "''")
                  switch($severity)
                  {
                      case "Fatal":   echo "<td class='deep-purple'>";    break;
                      case "Serious": echo "<td class='red lighten-1'>";  break;
                      default:        echo "<td class='grey lighten-1'>"; break;
                  }
              else
                  echo "<td class=".$color.">";
              echo $severity."</td>";
              
              // Priority
              $priority = $row['priority'];
              if($color == "''")
                  switch($priority)
                  {
                      case "Must Do":   echo "<td class='deep-purple'>";    break;
                      case "Medium": echo "<td class='orange lighten-1'>";  break;
                      case "High": echo "<td class='red lighten-1'>";  break;
                      default:        echo "<td class='grey lighten-1'>"; break;
                  }
                else
                    echo "<td class=".$color.">";
              echo $priority."</td>";

              // Deadline
              $deadline = $row['deadline'];
              if($color == "''")
              {
                  if($deadline != "Not scheduled")  echo "<td class='red lighten-1'>";
                  else                echo "<td class='grey lighten-1'>";
              }
              else
                  echo "<td class=".$color.">";
              echo $deadline."</td>";

              // Resolution
              switch($resolution)
              {
                  case "Deferred":                    echo "<td class='red lighten-1'>";          break;
                  case "Disagree With Suggestion":    echo "<td class='pink lighten-1'>";         break;
                  case "Duplicated":                  echo "<td class='red lighten-1'>";          break;
                  case "Fixed":                       echo "<td class='green lighten-1'>";        break;
                  case "Hold":                        echo "<td class='red lighten-1'>";          break;
                  case "Implemented":                 echo "<td class='green lighten-1'>";        break;
                  case "In Development":              echo "<td class='amber lighten-1'>";        break;
                  case "Known Problem":               echo "<td class='red lighten-1'>";          break;
                  case "Need More Info":              echo "<td class='pink lighten-1'>";         break;
                  case "New":                         echo "<td class='red lighten-1'>";          break;
                  case "Obsolete":                    echo "<td class='red lighten-1'>";          break;
                  case "Reeopen":                     echo "<td class='red lighten-1'>";          break;
                  case "Revised":                     echo "<td class='green lighten-1'>";        break;
                  case "Suggestion Not To Correct":   echo "<td class='pink lighten-1'>";         break;
                  case "Support Action Required":     echo "<td class='pink lighten-1'>";         break;
                  case "Withdrawn":                   echo "<td class='pink lighten-1'>";         break;
                  default:                            echo "<td class='grey lighten-1'>";         break;
              }
              echo $resolution."</td>";
                            
                            // End
              echo "</tr>";
            }

            $records->free_result()
          ?>
          </tbody>
           </table>
      </div>
    </div>
  </div>

<?php require_once("../footer.php"); ?>