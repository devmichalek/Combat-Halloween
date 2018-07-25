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
    	if($resolution == "Fixed" || $resolution == "Revised" || $resolution == "Implemented")
        $color = "'grey lighten-2'";
      
    	// Name
	    echo "<td class=".$color.">";
	    echo '<form action="edit/editbug.php" method="get">';
	    echo $row['name'];
	    echo '<input type="hidden" name="IDname" value="';
      	echo $row['IDname'].'"> ';
	    $descolor = ltrim($color, "'");
	    if($descolor == "")
	        $descolor = "cyan lighten-1'";
	    echo "<button type='submit' class='btn-floating ".$descolor."><i class='material-icons'>edit</i></button>";
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
	        if($row['developer'] == $author)
	            $descolor = "red lighten-1'";
	    }
	    
      
        echo "<a class='waves-effect waves-light btn modal-trigger ".$descolor." ";
        echo "href='#".$row['IDname']."'>";
        echo "Info</a></td>";
        echo "<div id='".$row['IDname']."' class='modal'>";
        echo "<div class='modal-content'>";
        echo "<h4 class='modcon'>".$row['name']." ID(".$row['IDname'].")</h4>";
        
        echo "<p class='japokki'>Reported by: ";
        echo '<div class="chip"><img src="../../images/users/'.$row['author'].'.jpg" alt="Contact Person"><span class="japokki">'.$row['author'].'</span></div>'."</p>";
        echo "<p class='japokki'>Developer: ";
        echo '<div class="chip"><img src="../../images/users/'.$row['developer'].'.jpg" alt="Contact Person"><span class="japokki">'.$row['developer'].'</span></div>'."</p>";
        
        echo "<p class='japokki'>Action to do: ".$row['action']."</p>";
        echo "<p class='japokki'>".$row['description']."</p>";
        echo "</div>";
        echo '<div class="modal-footer">';
        echo '<a href="#!" class="modal-close waves-effect waves-green btn-flat japokki">Ok</a>';
        echo "</div>";
        echo "</div>";

        // Location
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
	            case "Normal": echo "<td class='orange lighten-1'>";  break;
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
	        case "Deferred":                    echo "<td class='red lighten-1'>";        break;
	        case "Disagree":                    echo "<td class='pink lighten-1'>";       break;
	        case "Duplicated":                  echo "<td class='pink lighten-1'>";       break;
	        case "Fixed":                       echo "<td class='green lighten-1'>";      break;
	        case "Held":                        echo "<td class='red lighten-1'>";        break;
	        case "Implemented":                 echo "<td class='green lighten-1'>";      break;
	        case "In Development":              echo "<td class='amber lighten-1'>";      break;
	        case "Irreproducible":              echo "<td class='deep-purple'>";          break;
	        case "Known Problem":               echo "<td class='red lighten-1'>";        break;
	        case "Need More Info":              echo "<td class='blue lighten-1'>";       break;
	        case "New":                         echo "<td class='red lighten-1'>";        break;
	        case "Obsolete":                    echo "<td class='deep-purple'>";          break;
	        case "Reopen":                     echo "<td class='red lighten-1'>";        break;
	        case "Revised":                     echo "<td class='green lighten-1'>";      break;
	        case "Not To Correct":              echo "<td class='pink lighten-1'>";       break;
	        case "Support Needed":              echo "<td class='blue lighten-1'>";       break;
	        case "Withdrawn":                   echo "<td class='deep-purple'>";          break;
	        default:                            echo "<td class='grey lighten-1'>";       break;
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