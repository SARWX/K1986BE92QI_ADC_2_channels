import usb_cdc
import time

# Enable the data interface if it's not already enabled
usb_cdc.enable(console=True, data=True)

# Ensure that the data interface is available
if usb_cdc.data is None:
    raise RuntimeError("USB CDC data channel is not available.")

def send_packet(packet, max_retries=5, delay_between_retries=0.00001):
    retries = 0
    while retries < max_retries:
        try:
            # Send the packet
            bytes_written = usb_cdc.data.write(packet)
            usb_cdc.data.flush()  # Ensure all data is written
            print(f"Sent {bytes_written} bytes")

            # Wait for a short delay before retrying (if needed)
            time.sleep(delay_between_retries)

            # If the entire packet was written, we assume success
            if bytes_written == len(packet):
                print("Packet sent successfully.")
                return True  # Success
            else:
                print(f"Incomplete write, {bytes_written}/{len(packet)} bytes sent. Retrying...")
                retries += 1
        except Exception as e:
            print(f"Error occurred: {e}. Retrying...")
            retries += 1

    print("Failed to send packet after retries.")
    return False  # Failed after max retries

# Example usage for sending two packets
packet04 = bytes([4] * 64)
packet09 = bytes([9] * 64)

send_packet(packet04)
send_packet(packet09)
