<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:template match="/">
        <html>
            <body>
                <h2>Employee Details</h2>
                
                <table border="1" cellpadding="5">
                    <tr bgcolor="#B3E5FC">
                        <th>Employee ID</th>
                        <th>Employee Name</th>
                        <th>Employee Department</th>
                        <th>Employee Designation</th>
                        <th>Salary</th>
                    </tr>

                    <xsl:for-each select="employees/employee">
                        <tr>
                            <td><xsl:value-of select="@empId"/> </td>
                            <td><xsl:value-of select="name"/></td>
                            <td><xsl:value-of select="department"/></td>
                            <td><xsl:value-of select="designation"/></td>
                            <td><xsl:value-of select="salary"/></td>
                        </tr>
                    </xsl:for-each>
                </table>
            </body>
        </html>
    </xsl:template>
</xsl:stylesheet>