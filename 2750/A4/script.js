$(document).ready(function() {
  // hide all sections except the first one

  $("#rotate-svg-form").hide();
  $(".section").not(":first").hide();
  // handle navigation link clicks
  $(".nav-link").click(function() {
      // hide all sections
      $(".section").hide();


      // get the section to show
      var sectionToShow = $(this).data("section");

      // show the selected section
      $("#" + sectionToShow).show();

      // hide the add-element form if it is not the selected section
      if (sectionToShow !== "add-element") {
          $("#add-element").hide();
      }
      if (sectionToShow !== "view-molecule") {
          $("#rotate-svg-form").hide();
          $("#image-container").empty();
      }
      //change the html file name based on the section to show
      $("#html-file-name").html(sectionToShow + ".html");

  });
  if ($("#view-molecule").is(":visible")) {
      $("#rotate-svg-form").show();
  }
  $("#uploadSDF").submit(function(e) {
      alert("If the file was not previously uploaded, it will be uploaded now. If it was previously uploaded, please upload a new file. Please wait for the page to reload");
  })

  $.ajax({
      method: "GET",
      dataType: "json",
      url: "/element-page",
      success: function(data) {

          const tableBody = document.getElementById("element-table-body");
          for (let i = 0; i < data.length; i++) {
              const row = document.createElement("tr");
              const cell1 = document.createElement("td");
              cell1.appendChild(document.createTextNode(data[i][0]));
              const cell2 = document.createElement("td");
              cell2.appendChild(document.createTextNode(data[i][1]));
              const cell3 = document.createElement("td");
              const colorSpan = document.createElement("span");
              colorSpan.classList.add("color-preview");
              colorSpan.style.backgroundColor = data[i][2];
              cell3.appendChild(colorSpan);
              const cell4 = document.createElement("td");
              const button = document.createElement("button");
              button.innerHTML = "Remove";
              button.addEventListener("click", function() { // add a click event listener to the button
                  // Remove the row from the table
                  row.remove();

                  // Send a signal to the server to remove the corresponding element
                  var formData = {
                      "element-name": data[i][0],
                      "element-code": data[i][1],
                  }

                  $.ajax({
                      type: "POST",
                      url: "/delete-element",
                      data: formData,
                      contentType: "application/json",
                      success: function(response) {
                          console.log("Element removed successfully");
                      },
                  });
              });
              cell4.appendChild(button);
              row.appendChild(cell1);
              row.appendChild(cell2);
              row.appendChild(cell3);
              row.appendChild(cell4);
              tableBody.appendChild(row);
          }
      }

  });
  $("#add-element").submit(function(e) {
      e.preventDefault(); // prevent form submission

      var formData = {
          "element-number": $("#element-number").val() || 1,
          "element-code": $("#element-code").val() || "H",
          "element-name": $("#element-name").val() || "Hydrogen",
          "color1": $("#color1").val() || "#FFFFFF",
          "color2": $("#color2").val() || "#050505",
          "color3": $("#color3").val() || "#020202",
          "radius": $("#radius").val() || 25,
      };

      $.ajax({
          method: "POST",
          dataType: "json",
          url: "/element-page",
          data: formData,
          success: function(data) {
              if (data.message === "Element already exists in table") {
                  console.log("Element already exists");
                  alert("Element already exists in table");
              }
          }

      });
      location.reload();
  });


});




$.ajax({
  type: "GET",
  dataType: "json",
  url: "/moleculeDetails",
  success: function(data) {
      const tableBody = document.getElementById("mol-table-body");
      for (let i = 0; i < data.length; i++) {
          const row = document.createElement("tr");
          const cell1 = document.createElement("td");
          cell1.appendChild(document.createTextNode(data[i][0]));
          const cell2 = document.createElement("td");
          cell2.appendChild(document.createTextNode(data[i][1]));
          const cell3 = document.createElement("td");
          cell3.appendChild(document.createTextNode(data[i][2]));
          const cell4 = document.createElement("td"); // create fourth column
          const button = document.createElement("button"); // create button
          button.innerHTML = "Get SVG"; // set button text
          button.classList.add("get-svg-button"); // add class to button

          button.addEventListener("click", function(e) { // add event listener
              $("#rotate-svg-form").show();
              const moleculeId = data[i][0];
              const url = "/getSVG?id=" + moleculeId;
              e.preventDefault(); // prevent form submission
              $.ajax({
                  type: "GET",
                  dataType: "json", // specify response data type as text
                  url: url,
                  success: function(response) {
                      // handle response from back end
                      console.log("SVG received");
                      const imageContainer = document.getElementById("image-container"); // get the image container
                      if (imageContainer.childElementCount > 0) {
                          imageContainer.removeChild(imageContainer.firstChild);
                      }
                      imageContainer.innerHTML = response;
                  },
                  error: function(error) {
                      console.log(error);
                  }
              });
          });


          button.addEventListener("click", function() { // add event listener
              // show the rotate-svg-form only when it is on the view-molecule form

              const moleculeName = data[i][0];
              $("#rotate-svg-form").submit(function(e) {
                  e.preventDefault();

                  // get the rotation values
                  // get the rotation values as strings
                  var rotateX = $("#rotate-x").val();
                  var rotateY = $("#rotate-y").val();
                  var rotateZ = $("#rotate-z").val();
                  rotateX = parseInt(rotateX);
                  rotateY = parseInt(rotateY);
                  rotateZ = parseInt(rotateZ);

                  // Do something with the updated rotateX, rotateY, and rotateZ variables
                  if (rotateX === null || rotateX === undefined || !Number.isInteger(parseInt(rotateX))) {
                      rotateX = 0;
                  }

                  if (rotateY === null || rotateY === undefined || !Number.isInteger(parseInt(rotateY))) {
                      rotateY = 0;
                  }

                  if (rotateZ === null || rotateZ === undefined || !Number.isInteger(parseInt(rotateZ))) {
                      rotateZ = 0;
                  }
                  var formData = {
                      "rotate-x": rotateX,
                      "rotate-y": rotateY,
                      "rotate-z": rotateZ,
                      "mol-name": moleculeName
                  }
                  $.ajax({
                      type: "POST",
                      url: "/rotateSVG",
                      data: formData,
                      contentType: "application/json",
                      success: function(response) {
                          // handle response from back end
                          console.log("SVG rotated");

                          const imageContainer = document.getElementById("image-container"); // get the image container
                          if (imageContainer.childElementCount > 0) {
                              imageContainer.removeChild(imageContainer.firstChild);
                          }
                          imageContainer.innerHTML = response;
                      }
                  });
              });
          });
          cell4.appendChild(button); // append button to fourth column
          row.appendChild(cell1);
          row.appendChild(cell2);
          row.appendChild(cell3);
          row.appendChild(cell4); // append fourth column to row
          tableBody.appendChild(row);
      }
  }
});
